# Base64-AES-DES-SM4-MD5  

<h1 align="center">Hi 👋, I'm KANG TIAN LE</h1>
<h2 align="center">A developer from China</h2>
<h3 align="left">支持C/C++、C#语言的算法库：</h3>

* AES PKCS7填充算法
* SM4 PKCS7填充算法
* Base64编码
* DES算法
* MD5算法

<p align="left"> <img src="https://komarev.com/ghpvc/?username=leekasm&label=Profile%20views&color=0e75b6&style=flat" alt="leekasm" /> </p>

<p align="left"> <a href="https://github.com/ryo-ma/github-profile-trophy"><img src="https://github-profile-trophy.vercel.app/?username=leekasm" alt="leekasm" /></a> </p>
test code：<br>
　AES：<br>
　　C/C++：<br>
　　　const char* str = "测试字符";<br>
　　　char key[17] = { "thisIstheBestKey" };<br>
　　　char iv[17] = { 0x75, 0x52, 0x5f, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67, 0x21, 0x21,'\0' };<br>
　　　size_t retLength;<br>
　　　AES_CBC_PKCS7_ENCRYPT(key, iv, (uint8_t*)str, strlen(str), NULL, 0, &retLength);<br>
　　　uint8_t* encode_out = (uint8_t*)calloc(1, retLength);<br>
　　　bool bEncrypt = AES_CBC_PKCS7_ENCRYPT(key, iv, (uint8_t*)str, strlen(str), encode_out, retLength, &retLength);<br>
　　　AES_CBC_PKCS7_DECRYPT(key, iv, encode_out, retLength, NULL, 0, &retLength);<br>
　　　uint8_t* decode_out = (uint8_t*)calloc(1, retLength);<br>
　　　bool bDecrypt = AES_CBC_PKCS7_DECRYPT(key, iv, encode_out, retLength, decode_out, retLength, &retLength);<br>

　　C#：<br>
　　　byte[] str = Encoding.Default.GetBytes("测试字符");<br>
　　　Aes aes = new AesManaged() { Padding = PaddingMode.PKCS7, Mode = CipherMode.CBC, KeySize = 128 };<br>
　　　aes.Key = Encoding.Default.GetBytes("thisIstheBestKey");<br>
　　　aes.IV = new byte[] { 0x75, 0x52, 0x5f, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67, 0x21, 0x21 };<br>

　　　byte[] encode_out = null;<br>
　　　byte[] decode_out = null;<br>
　　　using (MemoryStream ms = new MemoryStream())<br>
　　　using (CryptoStream cs = new CryptoStream(ms, aes.CreateEncryptor(), CryptoStreamMode.Write))<br>
　　　{<br>
　　　　　cs.Write(str, 0, str.Length);<br>
　　　　　cs.FlushFinalBlock();<br>
　　　　　encode_out = ms.ToArray();<br>
　　　}<br>
　　　using (MemoryStream ms = new MemoryStream())<br>
　　　using (CryptoStream cs = new CryptoStream(ms, aes.CreateDecryptor(), CryptoStreamMode.Write))<br>
　　　{<br>
　　　　　cs.Write(encode_out, 0, encode_out.Length);<br>
　　　　　cs.FlushFinalBlock();<br>
　　　　　decode_out = ms.ToArray();<br>
　　　}<br>
<br>
　SM4：<br>
　　C/C++：<br>
　　　const char* str = "测试字符";<br>
　　　char key[17] = { "thisIstheBestKey" };<br>
　　　char iv[17] = { 0x75, 0x52, 0x5f, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67, 0x21, 0x21,'\0' };<br>
　　　size_t retLength;<br>
　　　SM4_CBC_PKCS7_ENCRYPT(key, iv, (uint8_t*)str, strlen(str), NULL, 0, &retLength);<br>
　　　uint8_t* encode_out = (uint8_t*)calloc(1, retLength);<br>
　　　bool bEncrypt = SM4_CBC_PKCS7_ENCRYPT(key, iv, (uint8_t*)str, strlen(str), encode_out, retLength, &retLength);<br>
　　　SM4_CBC_PKCS7_DECRYPT(key, iv, encode_out, retLength, NULL, 0, &retLength);<br>
　　　uint8_t* decode_out = (uint8_t*)calloc(1, retLength);<br>
　　　bool bDecrypt = SM4_CBC_PKCS7_DECRYPT(key, iv, encode_out, retLength, decode_out, retLength, &retLength);<br>
　　C#：<br>
　　　byte[] str = Encoding.Default.GetBytes("测试字符");<br>
　　　byte[] key = Encoding.Default.GetBytes("thisIstheBestKey");<br>
　　　byte[] iv = new byte[] { 0x75, 0x52, 0x5f, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67, 0x21, 0x21 };<br>
　　　int returnSize = 0;<br>
　　　byte[] encode_out = null;<br>
　　　byte[] decode_out = null;<br>
　　　Algorithm.SM4.SM4_CBC_PKCS7_ENCRYPT(key, iv, str, ref encode_out, out returnSize);<br>
　　　encode_out = new byte[returnSize];<br>
　　　bool bEncrypt = Algorithm.SM4.SM4_CBC_PKCS7_ENCRYPT(key, iv, str, ref encode_out, out returnSize);<br>
　　　Algorithm.SM4.SM4_CBC_PKCS7_DECRYPT(key, iv, encode_out, ref decode_out, out returnSize);<br>
　　　decode_out = new byte[returnSize];<br>
　　　bool bDecrypt = Algorithm.SM4.SM4_CBC_PKCS7_DECRYPT(key, iv, encode_out, ref decode_out, out returnSize);<br>
<br>
　Base64：<br>
　　C/C++：<br>
　　　const char* str = "测试字符";<br>
　　　char* encode_out = NULL;<br>
　　　char* decode_out = NULL;<br>
　　　size_t encode_size = 0;<br>
　　　size_t decode_size = 0;<br>
　　　base64_encode((char*)str, strlen(str), NULL, 0, &encode_size);<br>
　　　encode_out = (char*)calloc(1, encode_size + 1);<br>
　　　bool bEncrypt = base64_encode(str, strlen(str), encode_out, encode_size + 1, &encode_size);<br>
　　　base64_decode(encode_out, encode_size, NULL, 0, &decode_size);<br>
　　　decode_out = (char*)calloc(1, decode_size + 1);<br>
　　　bool bDecrypt = base64_decode(encode_out, encode_size, decode_out, decode_size + 1, &decode_size);<br>
　　C#：<br>
　　　string encode_out = Algorithm.Base64.base64_encode("测试字符");<br>
　　　int encode_size = Encoding.Default.GetByteCount(encode_out);<br>
　　　string decode_out = Algorithm.Base64.base64_decode(encode_out);<br>
　　　int decode_size = Encoding.Default.GetByteCount(decode_out);<br>
<br>
　DES：<br>
　　C/C++：<br>
　　　const char* str = "测试字符"; <br>
　　　InitDES("12345678", "87654321");<br>
　　　char* encode_out = EncryptDES(str);<br>
　　　char* decode_out = DecryptDES(encode_out);<br>
　　C#：<br>
　　　byte[] key = Encoding.Default.GetBytes("12345678");<br>
　　　byte[] iv = Encoding.Default.GetBytes("87654321");<br>
　　　Algorithm.DES.InitEDS(key, iv);<br>
　　　string encode_out = Algorithm.DES.EncryptDES("测试字符");<br>
　　　string decode_out = Algorithm.DES.DecryptDES(encode_out);<br>
<br>
　MD5：<br>
　　C/C++：<br>
　　　const char* str = "测试字符"; <br>
　　　char* encode_out = EncryptMD5(str);<br>
　　C#：<br>
　　　string encode_out = Algorithm.MD5.EncryptMD5("测试字符");<br>
<br>
<br>
- 📫 How to reach me **LeeKasm@gmail.com**

<h3 align="left">Connect with me:</h3>
<p align="left"></p>
<p><a href="https://www.buymeacoffee.com/LeeKasm"> <img align="left" src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="50" width="210" alt="LeeKasm" /></a></p><br><br>

<h3 align="left">Support:</h3>
<p>&nbsp;<img align="left" src="https://github-readme-stats.vercel.app/api?username=leekasm&show_icons=true&locale=en" alt="leekasm" /></p>
<p>&nbsp;<img align="left" src="https://github-readme-streak-stats.herokuapp.com/?user=leekasm&" alt="leekasm" /></p>
<p>&nbsp;<img align="left" src="https://github-readme-stats.vercel.app/api/top-langs?username=leekasm&show_icons=true&locale=en&layout=compact" alt="leekasm" /></p>

