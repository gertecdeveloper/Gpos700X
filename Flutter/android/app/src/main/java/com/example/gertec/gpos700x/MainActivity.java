package com.example.gertec.gpos700x;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import br.com.gertec.gedi.GEDI;
import br.com.gertec.gedi.exceptions.GediException;
import br.com.gertec.gedi.interfaces.IGEDI;
import io.flutter.embedding.android.FlutterActivity;
import io.flutter.embedding.engine.FlutterEngine;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugins.GeneratedPluginRegistrant;

public class MainActivity extends FlutterActivity {

    IGEDI iGedi;

    private static final String CHANNEL = "com.dev.app/channel_name";


    @Override
    public void configureFlutterEngine(@NonNull FlutterEngine flutterEngine) {
        GeneratedPluginRegistrant.registerWith(flutterEngine);

        new MethodChannel(flutterEngine.getDartExecutor().getBinaryMessenger(), CHANNEL)
                .setMethodCallHandler((call, result) -> {

                    GEDI.init(this);

                    new Thread(() -> {
                        iGedi = GEDI.getInstance(MainActivity.this);
                    }).start();


                    if (call.method.equals("powerManage")) {
                        try {

                            iGedi.getPRNTR().DrawBlankLine(100);
                            iGedi.getPRNTR().Output();
                        } catch (GediException e) {
                            e.printStackTrace();
                        }
                    }

                });
    }


}
