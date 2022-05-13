package com.example.gpos700x.ExemploNFCGedi;

import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.NfcAdapter;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.gpos700x.R;

import br.com.gertec.gedi.GEDI;
import br.com.gertec.gedi.interfaces.ICL;
import br.com.gertec.gedi.structs.GEDI_CL_st_ISO_PollingInfo;

public class NfcExemploGedi extends AppCompatActivity {

    private static final String TAG = NfcExemploGedi.class.getSimpleName();
    ICL icl = null;

    GEDI_CL_st_ISO_PollingInfo pollingInfo;

    private NfcAdapter nfcAdapter;

    private TextView text;

    private static int Contagem = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.nfcexemplogedi);

        text = findViewById(R.id.textIdCartao);

        new Thread(new Runnable() {
            @Override
            public void run() {
                GEDI.init(getApplicationContext());
            }
        }).start();
    }

    @Override
    protected void onStart() {
        super.onStart();
        // Liga o Sensor da NFC
        nfcAdapter = NfcAdapter.getDefaultAdapter(this);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        try {
            icl = GEDI.getInstance().getCL();
            // Inicializa a Leitura da NFC segura
            icl.PowerOn();
            pollingInfo = new GEDI_CL_st_ISO_PollingInfo();
            // Tempo que será aguardado para fazer a leitura
            pollingInfo = icl.ISO_Polling(100);
            icl.PowerOff();
            LerCard();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    @Override
    protected void onResume() {
        super.onResume();

        Log.d(TAG, "onResume");

        IntentFilter tagDetected = new IntentFilter(NfcAdapter.ACTION_TAG_DISCOVERED);
        IntentFilter ndefDetected = new IntentFilter(NfcAdapter.ACTION_NDEF_DISCOVERED);
        IntentFilter techDetected = new IntentFilter(NfcAdapter.ACTION_TECH_DISCOVERED);
        IntentFilter idDetected = new IntentFilter((NfcAdapter.EXTRA_ID));

        IntentFilter[] nfcIntentFilter = new IntentFilter[]{techDetected,tagDetected,ndefDetected, idDetected};

        PendingIntent pendingIntent = PendingIntent.getActivity(
                this, 0, new Intent(this, getClass()).addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP), 0);
        if(nfcAdapter!= null)
            nfcAdapter.enableForegroundDispatch(this, pendingIntent, nfcIntentFilter, null);

    }

    public void LerCard(){

        String mensagem;
        // Pega o Id do Cartão em Bytes
        mensagem = LerDados(pollingInfo.abUID);
        Contagem += 1;
        text.setText("Contador: " + Contagem +  "\nID Cartão: " + mensagem);

    }

    public String LerDados( byte[] dados) {

        long result = 0;

        if (dados == null) return "";

        for (int i = dados.length - 1; i >= 0; --i) {
            result <<= 8;
            result |= dados[i] & 0x0FF;
        }
        Log.d(TAG, "ID Cartão: " + Long.toString(result));
        Log.d(TAG, "ID Cartão HEX: " + bytesToHex(dados));
        
        return Long.toString(result);
    }

    private static String bytesToHex(byte[] hashInBytes) {

        StringBuilder sb = new StringBuilder();
        for (byte b : hashInBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}