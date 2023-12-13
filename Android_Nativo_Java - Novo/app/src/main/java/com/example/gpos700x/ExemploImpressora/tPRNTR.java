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
    import br.com.gertec.gedi.interfaces.ICL;
    import br.com.gertec.gedi.interfaces.IGEDI;
    import br.com.gertec.gedi.interfaces.IPRNTR;
    import br.com.gertec.gedi.structs.GEDI_PRNTR_st_BarCodeConfig;
    import br.com.gertec.gedi.structs.GEDI_PRNTR_st_PictureConfig;
    import br.com.gertec.gedi.structs.GEDI_PRNTR_st_StringConfig;


    public class tPRNTR extends AppCompatActivity {

        private static IGEDI iGedi = null;

        public static void DrawString(Context context, IPRNTR iprntr, String sAlign, int iOffset,
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
                        return;
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
                } catch (GediException e) {
                }
            } catch (IllegalArgumentException e) {
            }
        }

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
                //Cor
//                picconfig.color = true;


                //Print Data
                int id = context.getResources().getIdentifier(sDrawable, "drawable",
                        context.getPackageName());
                Bitmap bmp = BitmapFactory.decodeResource(context.getResources(), id);
                try {
                    ICL mCL = iGedi.getCL();
                    mCL.PowerOff();
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

        public static String DrawBarCode(IPRNTR iprntr, GEDI_PRNTR_e_BarCodeType barCodeType,
                                         int iHeight, int iWidth, String sData) {

            try {
                GEDI_PRNTR_st_BarCodeConfig barCodeConfig = new GEDI_PRNTR_st_BarCodeConfig();
//                GEDI_PRNTR_e_Alignment.CENTER;


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
