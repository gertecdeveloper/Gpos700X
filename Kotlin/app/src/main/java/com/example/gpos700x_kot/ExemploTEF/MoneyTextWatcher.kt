package com.example.gpos700x_kot.ExemploTEF

import android.text.Editable
import android.text.TextWatcher
import android.widget.EditText
import java.lang.ref.WeakReference
import java.math.BigDecimal
import java.text.NumberFormat
import java.util.Locale

class MoneyTextWatcher(editText: EditText, locale: Locale? = null) : TextWatcher {
    private val editTextWeakReference: WeakReference<EditText> = WeakReference(editText)
    private val locale: Locale = locale ?: Locale.getDefault()

    override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {
    }

    override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
    }

    override fun afterTextChanged(editable: Editable?) {
        val editText = editTextWeakReference.get()
        if (editText == null) return
        editText.removeTextChangedListener(this)
        val parsed = parseToBigDecimal(editable.toString().replace("R\$", ""))
        val formatted = NumberFormat.getCurrencyInstance(locale).format(parsed)
        editText.setText(formatted.replace("R\$", ""))
        editText.setSelection(formatted.length - 2)
        editText.addTextChangedListener(this)
    }

    private fun parseToBigDecimal(value: String): BigDecimal {
        val replaceable = "[%s,.\\s]".format(NumberFormat.getCurrencyInstance(locale).currency.symbol)
        val cleanString = value.replace(replaceable.toRegex(), "")
        return BigDecimal(cleanString)
            .setScale(2, BigDecimal.ROUND_FLOOR)
            .divide(BigDecimal(100), BigDecimal.ROUND_FLOOR)
    }
}