using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace Algorithm
{
    class DES
    {
        private static bool DES_Inited = false;
        private static byte[] DES_Key = new byte[8];
        private static byte[] DES_IV = new byte[8];


        /// <summary>
        /// 初始化DES算法
        /// </summary>
        /// <param name="key">8位密钥</param>
        /// <param name="iv">8位向量</param>
        public static void InitEDS(byte[] key, byte[] iv) 
        {
            if (!DES_Inited)
            {
                key.CopyTo(DES_Key, 0);
                iv.CopyTo(DES_IV, 0);
                DES_Inited = true;
            }
        }


        /// <summary>
        /// DES加密字符串
        /// </summary>
        /// <param name="encryptString">待加密的字符串</param>      
        /// <returns>加密成功返回加密后的字符串，失败返回空串 </returns>
        public static string EncryptDES(string encryptString)
        {
            try
            {
                byte[] inputByteArray = Encoding.UTF8.GetBytes(encryptString);
                DESCryptoServiceProvider dCSP = new DESCryptoServiceProvider();
                using (MemoryStream ms = new MemoryStream())
                using (CryptoStream cs = new CryptoStream(ms, dCSP.CreateEncryptor(DES_Key, DES_IV), CryptoStreamMode.Write))
                {
                    cs.Write(inputByteArray, 0, inputByteArray.Length);
                    cs.FlushFinalBlock();
                    return Convert.ToBase64String(ms.ToArray());
                }
            }
            catch
            {
                return "";
            }
        }


        /// <summary>
        /// DES解密字符串
        /// </summary>
        /// <param name="decryptString">待解密的字符串</param>
        /// <returns>解密成功返回解密后的字符串，失败返空串</returns>
        public static string DecryptDES(string decryptString)
        {
            try
            {
                byte[] inputByteArray = Convert.FromBase64String(decryptString);
                DESCryptoServiceProvider DCSP = new DESCryptoServiceProvider();
                using (MemoryStream ms = new MemoryStream())
                using (CryptoStream cs = new CryptoStream(ms, DCSP.CreateDecryptor(DES_Key, DES_IV), CryptoStreamMode.Write))
                {
                    cs.Write(inputByteArray, 0, inputByteArray.Length);
                    cs.FlushFinalBlock();
                    return Encoding.UTF8.GetString(ms.ToArray());
                }
            }
            catch
            {
                return "";
            }
        }
    }
}
