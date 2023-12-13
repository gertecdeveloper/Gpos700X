package com.example.gpos700x_kot

import android.content.Intent
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ListView
import android.widget.TextView
import com.example.gpos700x_kot.ExemploCodigoBarras1.CodigoBarras1
import com.example.gpos700x_kot.ExemploCodigoBarras2.CodigoBarras2
import com.example.gpos700x_kot.ExemploImpressora.Impressora
import com.example.gpos700x_kot.ExemploMifare.ExemploMifare
import com.example.gpos700x_kot.ExemploTEF.Tef

class MainActivity : AppCompatActivity() {


    companion object {
        const val G700X = "GPOS700X"
        private const val version = "v1.0.0"
        var Model = Build.MODEL
    }

    private val projetos = ArrayList<Projeto>()
    private lateinit var lvProjetos: ListView
    private lateinit var txtProject: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        lvProjetos = findViewById(R.id.lvProjetos)

        projetos.add(Projeto("Código de Barras", R.drawable.barcode))
        projetos.add(Projeto("Código de Barras V2", R.drawable.qr_code))
        projetos.add(Projeto("Impressão", R.drawable.print))

        if (Model == G700X) {
            projetos.add(Projeto("Mifare", R.drawable.nfc))
        }

        projetos.add(Projeto("TEF", R.drawable.tef))

        val adapter = ProjetoAdapter(applicationContext, R.layout.listprojetos, projetos)
        lvProjetos.adapter = adapter
        lvProjetos.setOnItemClickListener { _, view, i, _ ->
            val projeto = lvProjetos.getItemAtPosition(i) as Projeto

            var intent: Intent? = null
            when (projeto.nome) {
                "Código de Barras" -> intent = Intent(this@MainActivity, CodigoBarras1::class.java)
                "Código de Barras V2" -> intent = Intent(this@MainActivity, CodigoBarras2::class.java)
                "Impressão" -> intent = Intent(this@MainActivity, Impressora::class.java)
                "Mifare" -> intent = Intent(this@MainActivity, ExemploMifare::class.java)
                "TEF" -> intent = Intent(this@MainActivity, Tef::class.java)
            }
            if (intent != null) {
                startActivity(intent)
            }
        }
    }
}