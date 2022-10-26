namespace Algorithm
{
    class Base64
    {
        /// <summary>
        /// Base64加密
        /// </summary>
        /// <param name="input">输入字符串</param>
        /// <returns>输出字符串</returns>
        public static string base64_encode(string input) 
        {
            try
            {
                return System.Convert.ToBase64String(System.Text.Encoding.Default.GetBytes(input));
            }
            catch
            {
                return input;
            }
        }


        /// <summary>
        /// Base64解密
        /// </summary>
        /// <param name="input">输入字符串</param>
        /// <returns>输出字符串</returns>
        public static string base64_decode(string input)
        {
            try
            {
                return System.Text.Encoding.Default.GetString(System.Convert.FromBase64String(input));
            }
            catch
            {
                return input;
            }
        }
    }
}
