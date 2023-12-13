package com.example.gpos700x_kot.ExemploImpressora


import android.content.Context
import android.graphics.BitmapFactory
import android.graphics.Paint
import android.graphics.Typeface
import androidx.appcompat.app.AppCompatActivity
import br.com.gertec.gedi.enums.GEDI_PRNTR_e_Alignment
import br.com.gertec.gedi.enums.GEDI_PRNTR_e_BarCodeType
import br.com.gertec.gedi.exceptions.GediException
import br.com.gertec.gedi.interfaces.IGEDI
import br.com.gertec.gedi.interfaces.IPRNTR
import br.com.gertec.gedi.structs.GEDI_PRNTR_st_BarCodeConfig
import br.com.gertec.gedi.structs.GEDI_PRNTR_st_PictureConfig
import br.com.gertec.gedi.structs.GEDI_PRNTR_st_StringConfig

class tPRNTR : AppCompatActivity() {

    companion object {
        private var iGedi: IGEDI? = null

        fun DrawString(
            context: Context,
            iprntr: IPRNTR,
            sAlign: String,
            iOffset: Int,
            iLinespace: Int,
            sFont: String,
            bBold: Boolean,
            bItalic: Boolean,
            bUnderline: Boolean,
            fSize: Int,
            sData: String
        ) {
            try {
                var typeface = Typeface.create("NORMAL", Typeface.NORMAL)

                val strconfig = GEDI_PRNTR_st_StringConfig(Paint())

                //Align
                strconfig.paint.textAlign = Paint.Align.valueOf(sAlign)
                //Offset
                strconfig.offset = iOffset
                //LineSpace
                strconfig.lineSpace = iLinespace
                //Font
                if (sFont != "NORMAL") {
                    try {
                        typeface = Typeface.createFromAsset(
                            context.assets,
                            "fonts/$sFont"
                        )
                    } catch (e: Exception) {
                        return
                    }
                }
                //Bold & Italic
                if (bBold && bItalic)
                    typeface = Typeface.create(typeface, Typeface.BOLD_ITALIC)
                else if (bBold)
                    typeface = Typeface.create(typeface, Typeface.BOLD)
                else if (bItalic)
                    typeface = Typeface.create(typeface, Typeface.ITALIC)
                strconfig.paint.typeface = typeface
                //Underline
                if (bUnderline)
                    strconfig.paint.flags = Paint.UNDERLINE_TEXT_FLAG
                //Size
                strconfig.paint.textSize = fSize.toFloat()

                //Print Data
                try {
                    iprntr.Init()
                    iprntr.DrawStringExt(strconfig, sData)
                    iprntr.Output()
                } catch (e: GediException) {
                }
            } catch (e: IllegalArgumentException) {
            }
        }

        fun DrawPicture(
            context: Context,
            iprntr: IPRNTR,
            sAlign: String,
            iOffset: Int,
            iHeight: Int,
            iWidth: Int,
            sDrawable: String
        ): String {
            try {
                val picconfig = GEDI_PRNTR_st_PictureConfig()

                //Align
                picconfig.alignment = GEDI_PRNTR_e_Alignment.valueOf(sAlign)
                //Offset
                picconfig.height = iOffset
                //Height
                picconfig.height = iHeight
                //Width
                picconfig.width = iWidth


                //Print Data
                val id = context.resources.getIdentifier(sDrawable, "drawable", context.packageName)
                val bmp = BitmapFactory.decodeResource(context.resources, id)
                try {
                    val mCL = iGedi?.cl
                    mCL?.PowerOff()
                    iprntr.Init()
                    iprntr.DrawPictureExt(picconfig, bmp)
                    iprntr.Output()
                    return "0"
                } catch (e: GediException) {
                    return "tPRNTR_DrawPicture: $e"
                }
            } catch (e: IllegalArgumentException) {
                return "tPRNTR_DrawPicture: $e"
            }
        }

        fun DrawBarCode(
            iprntr: IPRNTR,
            barCodeType: GEDI_PRNTR_e_BarCodeType,
            iHeight: Int,
            iWidth: Int,
            sData: String
        ): String {
            try {
                val barCodeConfig = GEDI_PRNTR_st_BarCodeConfig()

                //Bar Code Type
                barCodeConfig.barCodeType = barCodeType
                //Height
                barCodeConfig.height = iHeight
                //Width
                barCodeConfig.width = iWidth

                //Print Data
                try {
                    iprntr.Init()
                    iprntr.DrawBarCode(barCodeConfig, sData)
                    iprntr.Output()
                    return "0"
                } catch (e: GediException) {
                    return "tPRNTR_DrawBarCode: $e"
                }
            } catch (e: IllegalArgumentException) {
                return "tPRNTR_DrawBarCode: $e"
            }
        }
    }
}
