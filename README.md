# Base64-AES-SM4-MD5
algorithm for C/C++/C#

`Base64：`  
  test code：  
    C/C++：  
      const char* str = "测试字符";  
      char* encode_out = (char*)malloc(BASE64_ENCODE_OUT_SIZE(strlen(str)));  
      int encode_size = base64_encode((char*)str, strlen(str), encode_out);  
      char* decode_out = (char*)malloc(BASE64_DECODE_OUT_SIZE(encode_size));  
      int decode_size = base64_decode(encode_out, encode_size, decode_out);  
  C#：  
      string encode_out = Algorithm.Base64.base64_encode("测试字符");  
      int encode_size = Encoding.Default.GetByteCount(encode_out);  
      string decode_out = Algorithm.Base64.base64_decode(encode_out);  
      int decode_size = Encoding.Default.GetByteCount(decode_out);  
