package com.example.gpos700x_kot.ExemploCodigoBarras2

import android.Manifest
import android.app.AlertDialog
import android.content.DialogInterface
import android.content.pm.PackageManager
import android.media.MediaPlayer
import android.os.Build
import android.os.Bundle
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.example.gpos700x_kot.R
import com.google.zxing.Result
import me.dm7.barcodescanner.zxing.ZXingScannerView

class CodigoBarras2 : AppCompatActivity(), ZXingScannerView.ResultHandler {

    private val ACESSO_NEGADO = "Permissão negada à câmera"
    private var flash = false
    private lateinit var contentFrame: ViewGroup
    private lateinit var mScannerView: ZXingScannerView
    private lateinit var txtLeitura: TextView
    //private lateinit var btnFlash: Button
    private var StartCameraFlag = 0

    companion object {
        const val G700x = "GPOS700"

    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.codigo_barras2)

        ActivityCompat.requestPermissions(
            this,
            arrayOf(Manifest.permission.CAMERA),
            1
        )

        txtLeitura = findViewById(R.id.textLeitura)

        //btnFlash = findViewById(R.id.btnLigarFlash)

//        btnFlash.setOnClickListener {
//            if (flash) {
//                mScannerView.flash = false
//                flash = false
//                btnFlash.text = "Flash - Desligado"
//            } else {
//                mScannerView.flash = true
//                flash = true
//                btnFlash.text = "Flash - Ligado"
//            }
//        }

        contentFrame = findViewById(R.id.content_frame)
        mScannerView = ZXingScannerView(this)
        contentFrame.addView(mScannerView)
    }

    override fun onResume() {
        super.onResume()
        startCamera()
    }

    override fun onPause() {
        super.onPause()
        mScannerView.stopCamera()
    }

    override fun onDestroy() {
        super.onDestroy()
        mScannerView?.stopCamera()
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        when (requestCode) {
            1 -> {
                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                } else {
                    Toast.makeText(this, ACESSO_NEGADO, Toast.LENGTH_SHORT).show()
                }
            }
        }
    }

    override fun handleResult(result: Result) {
        // Aciona o beep
        val mp: MediaPlayer = MediaPlayer.create(applicationContext, R.raw.beep)
        mp.start()

        val alertDialog = AlertDialog.Builder(this).create()
        alertDialog.setTitle("Código " + result.barcodeFormat)
        alertDialog.setMessage(result.barcodeFormat.toString() + ": " + result.text)
        alertDialog.setButton(
            AlertDialog.BUTTON_NEUTRAL, "OK",
            DialogInterface.OnClickListener { dialog, which ->
                dialog.dismiss()
                startCamera()
            })
        alertDialog.show()

        txtLeitura.text = result.barcodeFormat.toString() + ": " + result.text
    }

    protected fun startCamera() {
        contentFrame.visibility = View.VISIBLE
        mScannerView.setResultHandler(this)
        mScannerView.setAutoFocus(true)

        if (Build.MODEL == G700x) {
            if (StartCameraFlag == 0) {
                mScannerView.startCamera()
                StartCameraFlag = 1
            } else {
                mScannerView.resumeCameraPreview(this)
            }
        } else {
            mScannerView.startCamera()
        }
    }

    protected fun stopCamera() {
        mScannerView.stopCamera()
        contentFrame.visibility = View.INVISIBLE
    }
}
