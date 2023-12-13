package com.example.gpos700x_kot.ExemploCodigoBarras1

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.annotation.Nullable
import br.com.gertec.easylayer.zxing.google.zxingcore.BarcodeFormat
import com.example.gpos700x_kot.R
import com.google.zxing.integration.android.IntentIntegrator
import com.google.zxing.integration.android.IntentResult

class CodigoBarras1 : Activity(), View.OnClickListener{

    private lateinit var txtLeitura: TextView
    private lateinit var btnEan8: Button
    private lateinit var btnEan13: Button
    private lateinit var btnEan14: Button
    private lateinit var btnQrCode: Button
    private lateinit var qrScan: IntentIntegrator
    private lateinit var titulo: String
    private lateinit var tipoCode: String
    private val arrayListTipo = ArrayList<String>()

    companion object {
        private val ALLOWED_FORMATS = setOf(
            BarcodeFormat.EAN_8.ordinal,
            BarcodeFormat.EAN_13.ordinal,
            BarcodeFormat.QR_CODE.ordinal
        )
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.codigo_barras1)

        txtLeitura = findViewById(R.id.textLeitura)

        btnEan8 = findViewById(R.id.btnEan8)
        btnEan13 = findViewById(R.id.btnEan13)
        btnEan14 = findViewById(R.id.btnEan14)
        btnQrCode = findViewById(R.id.btnQrCode)

        btnEan8.setOnClickListener(this)
        btnEan13.setOnClickListener(this)
        btnEan14.setOnClickListener(this)
        btnQrCode.setOnClickListener(this)
    }

    override fun onClick(view: View) {
        arrayListTipo.clear()
        when (view.id) {
            R.id.btnEan8 -> {
                titulo = "EAN 8"
                tipoCode = "EAN_8"
            }
            R.id.btnEan13 -> {
                titulo = "EAN 13"
                tipoCode = "EAN_13"
            }
            R.id.btnEan14 -> {
                titulo = "EAN 14"
                tipoCode = "EAN_14"
            }
            R.id.btnQrCode -> {
                titulo = "QrCode"
                tipoCode = "QR_CODE"
            }
        }
        arrayListTipo.add(tipoCode)
        startCamera()
    }

    private fun startCamera() {
        qrScan = IntentIntegrator(this)
        qrScan.setPrompt("Digitalizar o código $titulo")
        qrScan.setBeepEnabled(true)
        qrScan.setBarcodeImageEnabled(true)
        qrScan.setTimeout(30000) // 30 * 1000 => 3 minutos
        qrScan.initiateScan(arrayListTipo)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, @Nullable data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        val intentResult = IntentIntegrator.parseActivityResult(requestCode, resultCode, data)
        val stringBuilder = StringBuilder(txtLeitura.text.toString())

        if (intentResult != null) {
            if (intentResult.contents == null) {
                stringBuilder.append("$tipoCode: Não foi possível ler o código.\n")
                txtLeitura.text = stringBuilder.toString()
            } else {
                try {
                    Log.i(tipoCode, intentResult.contents)
                    stringBuilder.append("$tipoCode: ${intentResult.contents}\n")
                    txtLeitura.text = stringBuilder.toString()
                } catch (e: Exception) {
                    e.printStackTrace()
                    stringBuilder.append("$tipoCode: Erro ${e.message}\n")
                    txtLeitura.text = stringBuilder.toString()
                }
            }
        } else {
            super.onActivityResult(requestCode, resultCode, data)
            stringBuilder.append("$tipoCode: Não foi possível fazer a leitura.\n")
            txtLeitura.text = stringBuilder.toString()
        }
    }

}