using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Collections.Generic;

namespace TcpBroadcastServer
{
    public class Server : IDisposable
    {
        private bool runSendDataThread { get; set; }
        private Thread sendDataThread { get; set; }

        private List<StateObject> activeConnections { get; set; }
        private object lockObjectConnection { get; set; }
        private Socket listener { get; set; }

        private int id_ = 0;
        private BroadcastContent broadcastContent;
        private bool doBroadcast;

        public Detectable<int> connectedCount;

        public Detectable<string> log;

        public Server()
        {
            lockObjectConnection = new object();
            activeConnections = new List<StateObject>();

            runSendDataThread = false;

            connectedCount = new Detectable<int>(0);
            log = new Detectable<string>("");

        }

        public class StateObject
        {
            public Socket workSocket = null;
            public const int BufferSize = 1024;
            public byte[] buffer = new byte[BufferSize];
            public StringBuilder sb = new StringBuilder();
            public int id;
        }

        public class BroadcastContent
        {
            public string Message;
            public int from_id;
        }

        public void Start(int port, bool _doBroadcast)
        {
            IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, port);
            listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                listener.Bind(localEndPoint);
                listener.Listen(100);
                listener.BeginAccept(new AsyncCallback(AcceptCallback), listener);
            }
            catch (Exception e)
            {
                log.Value = e.ToString();
            }

            // 送信スレッドを開始
            doBroadcast = _doBroadcast;
            runSendDataThread = true;
            sendDataThread = new Thread(new ThreadStart(SendMessageThread));
            sendDataThread.Start();

        }

        public void Stop()
        {
            runSendDataThread = false;
            sendDataThread.Join();
            sendDataThread = null;

            listener.Close();
            listener = null;

            lock (lockObjectConnection)
            {
                activeConnections.RemoveRange(0, activeConnections.Count);
            }
        }

        private void AcceptCallback(IAsyncResult ar)
        {
            try
            {
                var listener = (Socket)ar.AsyncState;
                Socket handler = listener.EndAccept(ar);

                var state = new StateObject();
                state.workSocket = handler;
                state.id = id_++;

                handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReadCallback), state);

                activeConnections.Add(state);
                connectedCount.Value = activeConnections.Count;

                log.Value = "Connected!";

                listener.BeginAccept(new AsyncCallback(AcceptCallback), listener);
            }
            catch (ObjectDisposedException)
            {
                log.Value = "Connection closed.";
                return;
            }

        }

        private void ReadCallback(IAsyncResult ar)
        {
            var content = string.Empty;
            var state = (StateObject)ar.AsyncState;
            Socket handler = state.workSocket;

            try
            {
                int bytesRead = handler.EndReceive(ar);
                if (bytesRead > 0)
                {
                    state.sb.Append(Encoding.UTF8.GetString(state.buffer, 0, bytesRead));
                    content = state.sb.ToString();

                    // 改行まで読んだら
                    if (content.IndexOf("\n") > -1)
                    {
                        log.Value = "Received: " + content.Replace("\n", "");

                        broadcastContent = new BroadcastContent();
                        broadcastContent.Message = content;
                        broadcastContent.from_id = state.id;

                        state.sb.Length = 0;

                        handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReadCallback), state);
                    }
                    else
                    {
                        handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReadCallback), state);
                    }

                }
                if (bytesRead == 0)
                {
                    lock (lockObjectConnection)
                    {
                        log.Value = "Disconnected.";

                        activeConnections.Remove(state);
                        connectedCount.Value = activeConnections.Count;

                    }
                }
            }
            catch (Exception e)
            {
                lock (lockObjectConnection)
                {
                    log.Value = e.ToString();

                    activeConnections.Remove(state);
                    connectedCount.Value = activeConnections.Count;

                }
            }

        }

        private void Send(Socket handler, string data)
        {
            byte[] byteData = Encoding.UTF8.GetBytes(data);
            handler.BeginSend(byteData, 0, byteData.Length, 0, new AsyncCallback(SendCallback), handler);
        }

        private void SendCallback(IAsyncResult ar)
        {
            try
            {
                Socket handler = (Socket)ar.AsyncState;
                int bytesSent = handler.EndSend(ar);

            }
            catch (Exception e)
            {
                log.Value = e.ToString();
            }

        }

        private void SendMessageThread()
        {
            while (runSendDataThread == true)
            {
                try
                {
                    lock (lockObjectConnection)
                    {
                        if (broadcastContent != null)
                        {
                            foreach (StateObject each in activeConnections)
                            {
                                if (!doBroadcast || each.id != broadcastContent.from_id)
                                {
                                    Send(each.workSocket, broadcastContent.Message);
                                }
                            }

                            broadcastContent = null;
                        }

                    }
                }
                catch (Exception e)
                {
                    log.Value = e.ToString();
                }

                Thread.Sleep(1000);

            }

            lock (lockObjectConnection)
            {
                foreach (StateObject each in activeConnections)
                {
                    each.workSocket.Close();
                }
            }

        }

        public void Dispose()
        {
            Stop();
        }
    }


}
