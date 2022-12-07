using System.Text;
using System.Security.Cryptography;

namespace Algorithm
{
    /// <summary>
    /// MD5加密类
    /// </summary>
    public class MD5
    {
        public static string EncryptMD5(string encryptString)
        {
            StringBuilder sb = new StringBuilder();
            using (MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider())
            {
                //将输入字符串转换为字节数组并计算哈希。
                byte[] data = md5.ComputeHash(Encoding.UTF8.GetBytes(encryptString));
                int length = data.Length;
                for (int i = 0; i < data.Length; i++)
                    sb.Append(data[i].ToString("X2"));

            }
            return sb.ToString();
        }
    }
}