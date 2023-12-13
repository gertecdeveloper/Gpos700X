package com.example.gpos700x;

public class Utils {

    public static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i + 1), 16));
        }
        return data;
    }

    public static String byteArrayToHexString(byte[] in) {
        final StringBuilder builder = new StringBuilder();
        for (byte b : in) {
            builder.append(String.format("%02X", b));
        }
        return builder.toString();
    }

    public static String byteArrayToHexString(byte[] in, int len) {
        int i = 0;
        final StringBuilder builder = new StringBuilder();
        for (byte b : in) {
            if (++i > len) break;
            builder.append(String.format("%02X", b));
        }
        return builder.toString();
    }

    public static String byteArrayToString(byte[] bArray){
        return new String(bArray).substring(0, new String(bArray).indexOf(0));
    }
}

