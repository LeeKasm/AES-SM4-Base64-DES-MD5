namespace Algorithm
{
    public class PKCS7
    {
        public static int PADDING_OUT_SIZE(int s) 
        {
            return ((s + 15) / 16) * 16;
        }


        public static int pkcs7_padding_pad_buffer(byte[] buffer, int data_length, int buffer_size, byte modulus)
        {

            byte pad_byte = (byte)(modulus - (data_length % modulus));
            if (data_length + pad_byte > buffer_size)
            {
                return -pad_byte;
            }
            int i = 0;
            while (i < pad_byte)
            {
                buffer[data_length + i] = pad_byte;
                i++;
            }
            return pad_byte;
        }


        public static bool pkcs7_padding_valid(byte[] buffer, int data_length, int buffer_size, byte modulus)
        {

            int expected_pad_byte = modulus - (data_length % modulus);
            if (data_length + expected_pad_byte > buffer_size)
            {
                return false;
            }
            int i = 0;
            while (i < expected_pad_byte)
            {
                if (buffer[data_length + i] != expected_pad_byte)
                {
                    return false;
                }
                i++;
            }
            return true;
        }


        public static int pkcs7_padding_data_length(byte[] buffer, int buffer_size, byte modulus)
        {

            /* test for valid buffer size */
            if (buffer_size % modulus != 0 ||
                buffer_size < modulus)
            {
                return 0;
            }
            byte padding_value;
            padding_value = buffer[buffer_size - 1];
            /* test for valid padding value */
            if (padding_value < 1 || padding_value > modulus)
            {
                return 0;
            }
            /* buffer must be at least padding_value + 1 in size */
            if (buffer_size < padding_value + 1)
            {
                return 0;
            }
            byte count = 1;
            buffer_size--;
            for (; count < padding_value; count++)
            {
                buffer_size--;
                if (buffer[buffer_size] != padding_value)
                {
                    return 0;
                }
            }
            return buffer_size;
        }
    }
}
