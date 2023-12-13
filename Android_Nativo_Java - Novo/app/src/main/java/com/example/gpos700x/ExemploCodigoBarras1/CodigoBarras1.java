package com.example.gpos700x.ExemploCodigoBarras1;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.example.gpos700x.R;
import com.google.zxing.BarcodeFormat;
import com.google.zxing.integration.android.IntentIntegrator;
import com.google.zxing.integration.android.IntentResult;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;


public class CodigoBarras1 extends Activity implements View.OnClickListener {

    private TextView txtLeitura;

    private Button btnEan8;
    private Button btnEan13;
    private Button btnEan14;
    private Button btnQrCode;

    private IntentIntegrator qrScan;

    private String titulo;
    private String tipoCode;

    //private ArrayList<String> arrayListTipo;
    private ArrayList<String> arrayListTipo = new ArrayList<>();
    private static final Set<Integer> ALLOWED_FORMATS = new HashSet<>(Arrays.asList(
            BarcodeFormat.EAN_8.ordinal(),
            BarcodeFormat.EAN_13.ordinal(),
            BarcodeFormat.QR_CODE.ordinal()
    ));


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.codigo_barras1);

        txtLeitura = findViewById(R.id.textLeitura);

        btnEan8 = findViewById(R.id.btnEan8);
        btnEan13 = findViewById(R.id.btnEan13);
        btnEan14 = findViewById(R.id.btnEan14);
        btnQrCode = findViewById(R.id.btnQrCode);

        btnEan8.setOnClickListener(this);
        btnEan13.setOnClickListener(this);
        btnEan14.setOnClickListener(this);
        btnQrCode.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {

        this.arrayListTipo = new ArrayList<>();

        if (view.getId() == R.id.btnEan8) {
            titulo = "EAN 8";
            tipoCode = "EAN_8";
        } else if (view.getId() == R.id.btnEan13) {
            titulo = "EAN 13";
            tipoCode = "EAN_13";
        } else if (view.getId() == R.id.btnEan14) {
            titulo = "EAN 14";
            tipoCode = "EAN_14";
        } else if (view.getId() == R.id.btnQrCode) {
            titulo = "QrCode";
            tipoCode = "QR_CODE";
        }


        arrayListTipo.add(this.tipoCode);
        startCamera();

    }
    private void startCamera(){
        qrScan = new IntentIntegrator(this);
        qrScan.setPrompt("Digitalizar o código " + titulo );
        qrScan.setBeepEnabled(true);
        qrScan.setBarcodeImageEnabled(true);
        qrScan.setTimeout(30000); // 30 * 1000 => 3 minutos
        qrScan.initiateScan(this.arrayListTipo);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        IntentResult intentResult = IntentIntegrator.parseActivityResult(requestCode, resultCode, data);

        StringBuilder stringBuilder = new StringBuilder(txtLeitura.getText().toString());

        if (intentResult != null) {
            //if qrcode has nothing in it
            if (intentResult.getContents() == null) {
                // Toast.makeText(this, "Result Not Found", Toast.LENGTH_LONG).show();
                stringBuilder.append(this.tipoCode +": Não foi possível ler o código.\n");
                txtLeitura.setText(stringBuilder.toString());
            } else {
                //if qr contains data
                try {

                    Log.i(this.tipoCode, intentResult.getContents());
                    stringBuilder.append(this.tipoCode + ": " + intentResult.getContents() + "\n");
                    txtLeitura.setText(stringBuilder.toString());


                } catch (Exception e) {
                    e.printStackTrace();
                    stringBuilder.append(this.tipoCode +": Erro " + e.getMessage() + "\n");
                    txtLeitura.setText(stringBuilder.toString());
                }
            }
        } else {
            super.onActivityResult(requestCode, resultCode, data);
            stringBuilder.append(this.tipoCode +": Não foi possível fazer a leitura.\n");
            txtLeitura.setText(stringBuilder.toString());
        }

    }

}
