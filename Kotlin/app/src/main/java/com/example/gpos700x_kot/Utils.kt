package com.example.gpos700x_kot

class Utils {

    fun hexStringToByteArray(s: String): ByteArray {
        val len = s.length
        val data = ByteArray(len / 2)
        var i = 0
        while (i < len) {
            data[i / 2] = (Character.digit(s[i], 16) shl 4 or Character.digit(s[i + 1], 16)).toByte()
            i += 2
        }
        return data
    }

    fun byteArrayToHexString(input: ByteArray): String {
        val builder = StringBuilder()
        for (b in input) {
            builder.append(String.format("%02X", b))
        }
        return builder.toString()
    }

    fun byteArrayToHexString(input: ByteArray, len: Int): String {
        var i = 0
        val builder = StringBuilder()
        for (b in input) {
            if (++i > len) break
            builder.append(String.format("%02X", b))
        }
        return builder.toString()
    }

    fun byteArrayToString(bArray: ByteArray): String {
        val nullIndex = bArray.indexOf(0.toByte())
        return String(bArray.sliceArray(0 until if (nullIndex >= 0) nullIndex else bArray.size))
    }
}