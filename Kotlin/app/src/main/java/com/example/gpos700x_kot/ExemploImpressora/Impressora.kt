package com.example.gpos700x_kot.ExemploImpressora

import android.app.AlertDialog
import android.content.DialogInterface
import android.graphics.BitmapFactory
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity
import br.com.gertec.gedi.GEDI
import br.com.gertec.gedi.enums.GEDI_PRNTR_e_Alignment
import br.com.gertec.gedi.enums.GEDI_PRNTR_e_BarCodeType
import br.com.gertec.gedi.enums.GEDI_PRNTR_e_Status
import br.com.gertec.gedi.exceptions.GediException
import br.com.gertec.gedi.interfaces.IGEDI
import br.com.gertec.gedi.interfaces.IPRNTR
import br.com.gertec.gedi.structs.GEDI_PRNTR_st_BarCodeConfig
import br.com.gertec.gedi.structs.GEDI_PRNTR_st_PictureConfig
import com.example.gpos700x_kot.R

class Impressora : AppCompatActivity() {

    private lateinit var txtMensagemImpressao: EditText
    private lateinit var btnStatusImpressora: Button
    private lateinit var btnImagem: Button
    private lateinit var btnBarCode: Button
    private lateinit var btnImprimir: Button
    private lateinit var btnCupon: Button

    private var iGedi: IGEDI? = null
    //    private var iPrint: IPRNTR? = null
    private var status: GEDI_PRNTR_e_Status? = null

    private lateinit var iprntr: IPRNTR
    private lateinit var prntrStatus: GEDI_PRNTR_e_Status
    private var prntrUsage: Int = 0
    private var gediVersion: String? = null
    lateinit var GEDI_PRNTR_e_BarCodeType: GEDI_PRNTR_e_BarCodeType

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.impressora)

        GEDI.init(this)

        Thread { iGedi = GEDI.getInstance(this@Impressora) }.start()


        btnStatusImpressora = findViewById(R.id.btnStatusImpressora)
        btnImprimir = findViewById(R.id.btnImprimir)
        btnImagem = findViewById(R.id.btnImagem)
        btnBarCode = findViewById(R.id.btnBarCode)
        //btnCupon = findViewById(R.id.btnCupon)


        btnStatusImpressora.setOnClickListener {
            iprntr = iGedi!!.getPRNTR() ?: return@setOnClickListener
            try {
                val GEDI_PRNTR_e_Status = iprntr.Status().toString()
                Log.v("status", GEDI_PRNTR_e_Status)
                showMessagem("Status Impressora", GEDI_PRNTR_e_Status)
            } catch (e: GediException) {
                e.printStackTrace()
            }
            Log.d("Gertec: ", "Printer Status = $status Paper Usage = $status")
        }

        btnImagem.setOnClickListener {
            iGedi = GEDI.getInstance(this@Impressora)
            iprntr = iGedi!!.getPRNTR() ?: return@setOnClickListener
            try {
                val picconfig = GEDI_PRNTR_st_PictureConfig()
                //Align
                picconfig.alignment = GEDI_PRNTR_e_Alignment.CENTER
                //Offset
                picconfig.height = 50
                //Height
                picconfig.height = 300
                //Width
                picconfig.width = 300


                //Print Data
                val bmp = BitmapFactory.decodeResource(resources, R.drawable.tef)
                try {
                    //Desliga o módulo contactless para evitar conflito com a impressora
                    val mCL = iGedi!!.getCL()
                    mCL?.PowerOff()
                    iprntr.Init()
                    iprntr.DrawPictureExt(picconfig, bmp)
                    iprntr.DrawBlankLine(50)
                    iprntr.Output()
                } catch (e: GediException) {
                    e.printStackTrace()
                    Log.v("Erro", "Ocorreu um erro na impressão da imagem")
                }
            } catch (e: IllegalArgumentException) {
                e.printStackTrace()
                Log.v("Erro", "Ocorreu um erro na configuração da imagem")
            }
        }

        btnImprimir.setOnClickListener {
            try {
                txtMensagemImpressao = findViewById(R.id.txtMensagemImpressao)
                iprntr = iGedi!!.getPRNTR() ?: return@setOnClickListener
                val GEDI_PRNTR_e_Status = iprntr.Status().toString()
                Log.v("status", GEDI_PRNTR_e_Status)
                tPRNTR.DrawString(
                    this@Impressora, iprntr, "CENTER", 20, 20,
                    "NORMAL", true, false, false, 20, txtMensagemImpressao.text.toString()
                )
                iprntr.DrawBlankLine(50)
            } catch (e: GediException) {
                e.printStackTrace()
            }
        }

        btnBarCode.setOnClickListener {
            iGedi = GEDI.getInstance(this@Impressora)
            iprntr = iGedi!!.getPRNTR() ?: return@setOnClickListener
            try {
                val barCodeConfig = GEDI_PRNTR_st_BarCodeConfig()
                //Bar Code Type, use QR_CODE
                barCodeConfig.barCodeType =
                    br.com.gertec.gedi.enums.GEDI_PRNTR_e_BarCodeType.QR_CODE
                //Height
                barCodeConfig.height = 380
                //Width
                barCodeConfig.width = 380
                //Print Data
                //Desliga o módulo contactless para evitar conflito com a impressora
                val mCL = iGedi?.getCL()
                mCL?.PowerOff()
                iprntr.Init()
                //Insira o texto que deseja imprimir
                iprntr.DrawBarCode(barCodeConfig, "Print Custom String")
                iprntr.DrawBlankLine(80)
                iprntr.Output()
            } catch (e: GediException) {
                e.printStackTrace()
                Log.v("Erro", "Ocorreu um erro na impressão do QR texto")
            } catch (e: IllegalArgumentException) {
                e.printStackTrace()
                Log.v("Erro", "Ocorreu um erro na configuração do QR")
            }
        }

//        btnCupon.setOnClickListener {
//            iGedi = GEDI.getInstance(this@Impressora)
//            iprntr = iGedi!!.getPRNTR() ?: return@setOnClickListener
//            try {
//                val picconfig = GEDI_PRNTR_st_PictureConfig()
//                //Align
//                picconfig.alignment = GEDI_PRNTR_e_Alignment.CENTER
//                //Offset
//                picconfig.height = 50
//                //Height
//                picconfig.height = 2000
//                //Width
//                picconfig.width = 500
//
//
//                //Print Data
//                val bmp = BitmapFactory.decodeResource(resources, R.drawable.cupon)
//                try {
//                    //Desliga o módulo contactless para evitar conflito com a impressora
//                    val mCL = iGedi!!.getCL()
//                    mCL?.PowerOff()
//                    iprntr.Init()
//                    iprntr.DrawPictureExt(picconfig, bmp)
//                    iprntr.DrawBlankLine(100)
//                    iprntr.Output()
//                } catch (e: GediException) {
//                    e.printStackTrace()
//                    Log.v("Erro", "Ocorreu um erro na impressão da imagem")
//                }
//            } catch (e: IllegalArgumentException) {
//                e.printStackTrace()
//                Log.v("Erro", "Ocorreu um erro na configuração da imagem")
//            }
//        }

    }

    private fun showMessagem(titulo: String, mensagem: String) {
        val alertDialog = AlertDialog.Builder(this@Impressora).create()
        alertDialog.setTitle(titulo)
        alertDialog.setMessage(mensagem)
        alertDialog.setButton(
            AlertDialog.BUTTON_NEUTRAL,
            "OK"
        ) { dialog: DialogInterface, which: Int -> dialog.dismiss() }
        alertDialog.show()
    }

    private fun ShowFalha(sStatus: String) {
        showMessagem("Falha Impressora", sStatus)
    }
}