/*======================================= GERTEC =======================================
  File          : tPRNTR.java
  Project       : Gedi Test
  Platform      : Android
  Device        : Android POS devices
  Creation Date : 31/Aug/2018
  Author        : Vinícius Moreira

  Description   : tPRNTR.java:
                   - Android POS devices printer test functions parameters treatment
  ======================================== HISTORY ========================================
  When       Who                   What
  ---------  --------------------  --------------------------------------------------------
  31/08/18   Vinícius Moreira      - Initial version
  =========================================================================================*/

package com.example.gpos700x.ExemploImpressora;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Paint;
import android.graphics.Typeface;

import androidx.appcompat.app.AppCompatActivity;

import br.com.gertec.gedi.enums.GEDI_PRNTR_e_Alignment;
import br.com.gertec.gedi.enums.GEDI_PRNTR_e_BarCodeType;
import br.com.gertec.gedi.exceptions.GediException;
import br.com.gertec.gedi.interfaces.IPRNTR;
import br.com.gertec.gedi.structs.GEDI_PRNTR_st_BarCodeConfig;
import br.com.gertec.gedi.structs.GEDI_PRNTR_st_PictureConfig;
import br.com.gertec.gedi.structs.GEDI_PRNTR_st_StringConfig;

public class tPRNTR extends AppCompatActivity {

    /* tPRNTR_DrawString
    Print String Routine
    Input:
        Context context - getApplicationContext();
        iGedi - Gedi Instance;
        String sAlign - LEFT, CENTER or RIGHT;
        int iOffset - Left offset, default 0;
        int iLinespace - Linespace, default 0;
        String sFont - NORMAL or path to custom font;
        Boolean bBold - True for BOLD;
        Boolean bItalic - True for Italic;
        Boolean bUnderline - True for Underline;
        Float fSize - Font Size;
        String sData - Data to be printed;
    Output:
        N/A
    Return:
        OK - 0; NOK - Exception*/
    public static String DrawString(Context context, IPRNTR iprntr, String sAlign, int iOffset,
                                    int iLinespace, String sFont, Boolean bBold, Boolean bItalic,
                                    Boolean bUnderline, int fSize, String sData) {

        try {
            Typeface typeface = Typeface.create("NORMAL", Typeface.NORMAL);

            GEDI_PRNTR_st_StringConfig strconfig = new GEDI_PRNTR_st_StringConfig(new Paint());

            //Align
            strconfig.paint.setTextAlign(Paint.Align.valueOf(sAlign));
            //Offset
            strconfig.offset = iOffset;
            //LineSpace
            strconfig.lineSpace = iLinespace;
            //Font
            if (!sFont.equals("NORMAL")) {
                try {
                    typeface = Typeface.createFromAsset(context.getAssets(),
                            "fonts/" + sFont);
                } catch (Exception e) {
                    return "Font Error: " + e;
                }
            }
            //Bold & Italic
            if (bBold && bItalic)
                typeface = Typeface.create(typeface, Typeface.BOLD_ITALIC);
            else if (bBold)
                typeface = Typeface.create(typeface, Typeface.BOLD);
            else if (bItalic)
                typeface = Typeface.create(typeface, Typeface.ITALIC);
            strconfig.paint.setTypeface(typeface);
            //Underline
            if (bUnderline)
                strconfig.paint.setFlags(Paint.UNDERLINE_TEXT_FLAG);
            //Size
            strconfig.paint.setTextSize(fSize);

            //Print Data
            try {
                iprntr.Init();
                iprntr.DrawStringExt(strconfig, sData);
                iprntr.Output();
                return "0";
            } catch (GediException e) {
                return "tPRNTR_DrawString: " + e;
            }
        } catch (IllegalArgumentException e) {
            return "tPRNTR_DrawString: " + e;
        }
    }

    /* tPRNTR_DrawPicture
    Print String Routine
    Input:
        Context context - getApplicationContext();
        iprntr - Gedi Printer Instance;
        String sAlign - LEFT, CENTER or RIGHT;
        int iOffset - Left offset, default 0;
        int iHeight - Height of the picture, 0 to default height.
        int iWidth - Width of the picture, - to default width.
        String sDrawable - Name of the bmp picture - must be in drawable folder;
    Output: N/A
    Return: OK - 0; NOK - Exception*/
    public static String DrawPicture(Context context, IPRNTR iprntr, String sAlign, int iOffset,
                                     int iHeight, int iWidth, String sDrawable) {

        try {
            GEDI_PRNTR_st_PictureConfig picconfig = new GEDI_PRNTR_st_PictureConfig();

            //Align
            picconfig.alignment = GEDI_PRNTR_e_Alignment.valueOf(sAlign);
            //Offset
            picconfig.height = iOffset;
            //Height
            picconfig.height = iHeight;
            //Width
            picconfig.width = iWidth;

            //Print Data
            int id = context.getResources().getIdentifier(sDrawable, "drawable",
                    context.getPackageName());
            Bitmap bmp = BitmapFactory.decodeResource(context.getResources(), id);
            try {
                iprntr.Init();
                iprntr.DrawPictureExt(picconfig, bmp);
                iprntr.Output();
                return "0";
            } catch (GediException e) {
                return "tPRNTR_DrawPicture: " + e;
            }
        } catch (IllegalArgumentException e) {
            return "tPRNTR_DrawPicture: " + e;
        }
    }

    /* tPRNTR_DrawBarCode
    Print Bar Code Routine
    Input:
        iprntr - Gedi Printer Instance;
        GEDI_PRNTR_e_BarCodeType barCodeType - See GEDI documentation;
        int iHeight - Height of the barcode.
        int iWidth - Width of the barcode.
        String sData - Data to be printed;
    Output: N/A
    Return: OK - 0; NOK - Exception*/
    public static String DrawBarCode(IPRNTR iprntr, GEDI_PRNTR_e_BarCodeType barCodeType,
                                     int iHeight, int iWidth, String sData) {

        try {
            GEDI_PRNTR_st_BarCodeConfig barCodeConfig = new GEDI_PRNTR_st_BarCodeConfig();

            //Bar Code Type
            barCodeConfig.barCodeType = barCodeType;
            //Height
            barCodeConfig.height = iHeight;
            //Width
            barCodeConfig.width = iWidth;

            //Print Data
            try {
                iprntr.Init();
                iprntr.DrawBarCode(barCodeConfig, sData);
                iprntr.Output();
                return "0";
            } catch (GediException e) {
                return "tPRNTR_DrawBarCode: " + e;
            }
        } catch (IllegalArgumentException e) {
            return "tPRNTR_DrawBarCode: " + e;
        }
    }
}
