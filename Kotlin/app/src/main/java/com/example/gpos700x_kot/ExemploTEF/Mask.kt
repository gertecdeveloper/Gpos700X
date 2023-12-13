package com.example.gpos700x_kot.ExemploTEF

import android.text.Editable
import android.text.TextWatcher
import android.widget.EditText

abstract class Mask {
    companion object {
        fun insert(mask: String, et: EditText): TextWatcher {
            return object : TextWatcher {

                private var isUpdating = false
                private var oldTxt = ""

                override fun beforeTextChanged(
                    charSequence: CharSequence,
                    i: Int,
                    i1: Int,
                    i2: Int
                ) {
                }

                override fun onTextChanged(
                    s: CharSequence,
                    start: Int,
                    before: Int,
                    count: Int
                ) {
                    val str = unmask(s.toString())
                    var maskCurrent = ""
                    if (isUpdating) {
                        oldTxt = str
                        isUpdating = false
                        return
                    }
                    var i = 0
                    mask.toCharArray().forEach { m ->
                        if (m != '#' && str.length > oldTxt.length) {
                            maskCurrent += m
                            return@forEach
                        }
                        try {
                            maskCurrent += str[i]
                        } catch (e: Exception) {
                            return@forEach
                        }
                        i++
                    }
                    isUpdating = true
                    et.setText(maskCurrent)
                    et.setSelection(maskCurrent.length)
                }

                override fun afterTextChanged(editable: Editable) {
                }
            }
        }

        fun unmask(s: String): String {
            return s.replace("[.]".toRegex(), "")
                .replace("[-]".toRegex(), "")
                .replace("[:]".toRegex(), "")
                .replace("[/]".toRegex(), "")
                .replace("[(]".toRegex(), "")
                .replace(",".toRegex(), "")
                .replace("[)]".toRegex(), "")
                .replace("[R$]".toRegex(), "")
                .trim()
        }

    }
}