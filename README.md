# Base64-AES-SM4-MD5
algorithm for C/C++/C#

Base64：<br>
  test code：<br>
    C/C++：<br>
      const char* str = "测试字符";<br>
      char* encode_out = (char*)malloc(BASE64_ENCODE_OUT_SIZE(strlen(str)));<br>
      int encode_size = base64_encode((char*)str, strlen(str), encode_out);<br>
      char* decode_out = (char*)malloc(BASE64_DECODE_OUT_SIZE(encode_size));<br>
      int decode_size = base64_decode(encode_out, encode_size, decode_out);<br>
  C#：<br>
      string encode_out = Algorithm.Base64.base64_encode("测试字符");<br>
      int encode_size = Encoding.Default.GetByteCount(encode_out);<br>
      string decode_out = Algorithm.Base64.base64_decode(encode_out);<br>
      int decode_size = Encoding.Default.GetByteCount(decode_out);<br>
