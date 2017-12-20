using System;

namespace TcpBroadcastServer
{
    /// <summary>
    /// 変更を検知できるクラス
    /// </summary>
    public class Detectable<T>
    {
        private T mValue;   // 値

        /// <summary>
        /// <para>値を取得または設定します</para>
        /// <para>値の設定後に mChanged イベントが呼び出されます</para>
        /// </summary>
        public T Value
        {
            get { return mValue; }
            set
            {
                bool isChanged = !mValue.Equals(value);
                mValue = value;
                if (isChanged)
                    OnChanged(mValue);
            }
        }

        /// <summary>
        /// 値が変更された時に呼び出されます
        /// </summary>
        public Action<T> mChanged;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public Detectable()
        {
            mValue = default(T);
        }

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public Detectable(T value)
        {
            mValue = value;
        }

        /// <summary>
        /// 値が変更された時に呼び出されます
        /// </summary>
        private void OnChanged(T value)
        {
            var onChanged = mChanged;
            if (onChanged == null)
            {
                return;
            }
            onChanged(value);
        }
    }
}
