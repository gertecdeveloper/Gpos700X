package com.example.gpos700x_kot.ExemploTEF

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.text.InputType
import android.text.method.DigitsKeyListener
import android.widget.Button
import android.widget.CheckBox
import android.widget.EditText
import android.widget.RadioButton
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import br.com.gertec.gedi.GEDI
import br.com.gertec.gedi.enums.GEDI_PRNTR_e_Status
import br.com.gertec.gedi.exceptions.GediException
import br.com.gertec.gedi.interfaces.IGEDI
import br.com.gertec.gedi.interfaces.IPRNTR
import com.example.gpos700x_kot.ExemploImpressora.tPRNTR
import com.example.gpos700x_kot.R
import com.google.gson.Gson
import org.json.JSONException
import org.json.JSONObject
import java.text.DateFormat
import java.util.*
import java.util.regex.Pattern

class Tef : AppCompatActivity() {
    private val GER7_API_VERSION = "1.04"

    private val GER7_CREDITO = "1"
    private val GER7_DEBITO = "2"
    private val GER7_VOUCHER = "4"
    private val GER7_REIMPRESSAO = "18"

    private val GER7_SEMPARCELAMENTO = "0"
    private val GER7_PARCELADO_LOJA = "1"
    private val GER7_PARCELADO_ADM = "2"

    private val GER7_DESABILITA_IMPRESSAO = "0"
    private val GER7_HABILITA_IMPRESSAO = "1"

    private val GER7_VENDA = "1"
    private val GER7_CANCELAMENTO = "2"
    private val GER7_FUNCOES = "3"
    public var acao = "venda"
    private val gson = Gson()

    private val intentGer7 = Intent(Intent.ACTION_VIEW, Uri.parse("pos7api://pos7"))


    private var iGedi: IGEDI? = null
    //    private var iPrint: IPRNTR? = null
    private var status: GEDI_PRNTR_e_Status? = null

    private var iprntr: IPRNTR? = null

    // Difines operação
    private val r = Random()
    private val dt = Date()
    private val op = r.nextInt(99999).toString()
    private val currentDateTimeString = DateFormat.getDateInstance().format(Date())
    private val currentDateTimeStringT = "${dt.hours}${dt.minutes}${dt.seconds}"
    // Fim Defines Operação

    private val mLocale = Locale("pt", "BR")

    // Defines tef
    private val REQ_CODE = 4321

    private lateinit var venda: Venda
    private lateinit var txtValorOperacao: EditText
    private lateinit var txtIpServidor: EditText
    private lateinit var txtParcelas: EditText

    private lateinit var btnEnviarTransacao: Button
    private lateinit var btnCancelarTransacao: Button
    private lateinit var btnFuncoes: Button
    private lateinit var btnReimpressao: Button

    private lateinit var cbImpressao: CheckBox

    private lateinit var rbTodos: RadioButton
    private lateinit var rbCredito: RadioButton
    private lateinit var rbDebito: RadioButton
    private lateinit var rbGer7: RadioButton
    private lateinit var rbLoja: RadioButton
    private lateinit var rbAdm: RadioButton
    private lateinit var rbMsitef: RadioButton
    private lateinit var GEDI_PRNTR_e_Status: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.tef)

        venda = Venda()

        GEDI.init(this)

        Thread {
            iGedi = GEDI.getInstance(this@Tef)
        }.start()

        // Inicializa todos os EditText
        txtValorOperacao = findViewById(R.id.txtValorOperacao)
        txtIpServidor = findViewById(R.id.txtIpServidor)
        txtParcelas = findViewById(R.id.txtParcelas)

        // Inicializa todos os Buttons
        btnEnviarTransacao = findViewById(R.id.btnEnviarTransacao)
        btnCancelarTransacao = findViewById(R.id.btnCancelarTransacao)
        btnFuncoes = findViewById(R.id.btnFuncoes)
        btnReimpressao = findViewById(R.id.btnReimpressao)

        // Inicializa todos os RadioButtons

        rbCredito = findViewById(R.id.rbCredito)
        rbDebito = findViewById(R.id.rbDebito)
        rbTodos = findViewById(R.id.rbTodos)
        rbLoja = findViewById(R.id.radioLoja)
        rbAdm = findViewById(R.id.radioAdm)

        // Inicializa o CheckBox

        //* Caso seja M-sitef, este parâmetro não surge efeito (linhas comentadas na funções do M-Sitef (Abaixo)), pois na versão v3.70 está opção foi removida do Sitef **
        cbImpressao = findViewById(R.id.cbImpressao)
        cbImpressao.isEnabled = false
        cbImpressao.isChecked = false

        rbGer7 = findViewById(R.id.rbGer7)
        rbMsitef = findViewById(R.id.rbMsitef)
        // Adiciona mascara nos campos
        maskTextEdits()
        //txtValorOperacao.setHint("");
        txtValorOperacao.setText("1000")
        txtIpServidor.setText("")
        rbMsitef.isChecked = true
        rbAdm.isChecked = true
        cbImpressao.isChecked = true
        txtIpServidor.inputType = InputType.TYPE_CLASS_NUMBER
        txtIpServidor.keyListener = DigitsKeyListener.getInstance("0123456789.")
        rbDebito.setOnCheckedChangeListener { _, _ ->
            if (rbTodos.isChecked || rbDebito.isChecked) {
                txtParcelas.setText("1")
                txtParcelas.isEnabled = false
            } else {
                txtParcelas.isEnabled = true
            }
        }

        rbTodos.setOnCheckedChangeListener { _, _ ->
            if (rbTodos.isChecked || rbDebito.isChecked) {
                txtParcelas.setText("1")
                txtParcelas.isEnabled = false
            } else {
                txtParcelas.isEnabled = true
            }
        }

        rbMsitef.setOnCheckedChangeListener { _, _ ->
            if (rbMsitef.isChecked) {
                cbImpressao.isChecked = false
                cbImpressao.isEnabled =
                    false // * Caso seja M-sitef, este parâmetro não surge efeito (linhas comentadas na funções do M-Sitef (Abaixo)), pois na versão v3.70 está opção foi removida do Sitef **
                txtIpServidor.isEnabled = true
            } else {
                cbImpressao.isEnabled = true
                txtIpServidor.isEnabled = false
            }
        }

        btnEnviarTransacao.setOnClickListener {
            acao = "venda"
            if (Mask.unmask(txtValorOperacao.text.toString()) == "000") {
                dialogoErro("O valor de venda digitado deve ser maior que 0")
            } else if (rbMsitef.isChecked && !validaIp(txtIpServidor.text.toString())) {
                dialogoErro("Digite um IP válido")
            } else {
                if (rbCredito.isChecked && (txtParcelas.text.toString()
                        .isEmpty() || txtParcelas.text.toString() == "0")
                ) {
                    dialogoErro("É necessário colocar o número de parcelas desejadas (obs.: Opção de compra por crédito marcada)")
                } else {
                    if (rbGer7.isChecked) {
                        execulteGer7Venda()
                    } else if (rbMsitef.isChecked) {
                        execulteSTefVenda()
                    }
                }
            }
        }

        btnCancelarTransacao.setOnClickListener {
            acao = "cancelamento"
            if (Mask.unmask(txtValorOperacao.text.toString()) == "000") {
                dialogoErro("O valor de venda digitado deve ser maior que 0")
            } else if (rbMsitef.isChecked && !validaIp(txtIpServidor.text.toString())) {
                dialogoErro("Digite um IP válido")
            } else {
                if (rbMsitef.isChecked) {
                    execulteSTefCancelamento()
                } else {
                    execulteGer7Cancelamento()
                }
            }
        }

        btnFuncoes.setOnClickListener {
            acao = "funcoes"
            if (Mask.unmask(txtValorOperacao.text.toString()) == "000") {
                dialogoErro("O valor de venda digitado deve ser maior que 0")
            } else if (rbMsitef.isChecked && !validaIp(txtIpServidor.text.toString())) {
                dialogoErro("Digite um IP válido")
            } else {
                if (rbMsitef.isChecked) {
                    execulteSTefFuncoes()
                } else {
                    execulteGer7Funcoes()
                }
            }
        }

        btnReimpressao.setOnClickListener {
            acao = "reimpressao"
            if (Mask.unmask(txtValorOperacao.text.toString()) == "000") {
                dialogoErro("O valor de venda digitado deve ser maior que 0")
            } else if (rbMsitef.isChecked && !validaIp(txtIpServidor.text.toString())) {
                dialogoErro("Digite um IP válido")
            } else {
                if (rbMsitef.isChecked) {
                    execulteSTefReimpressao()
                } else {
                    execulteGer7Reimpressao()
                }
            }
        }
    }

    // O M-Sitef não retorna um json como resposta, logo é criado um json com a
    // reposta do Sitef.
    @Throws(JSONException::class)
    fun respSitefToJson(data: Intent?): String {
        val json = JSONObject()
        json.put("CODRESP", data?.getStringExtra("CODRESP"))
        json.put("COMP_DADOS_CONF", data?.getStringExtra("COMP_DADOS_CONF"))
        json.put("CODTRANS", data?.getStringExtra("CODTRANS"))
        json.put("VLTROCO", data?.getStringExtra("VLTROCO"))
        json.put("REDE_AUT", data?.getStringExtra("REDE_AUT"))
        json.put("BANDEIRA", data?.getStringExtra("BANDEIRA"))
        json.put("NSU_SITEF", data?.getStringExtra("NSU_SITEF"))
        json.put("NSU_HOST", data?.getStringExtra("NSU_HOST"))
        json.put("COD_AUTORIZACAO", data?.getStringExtra("COD_AUTORIZACAO"))
        json.put("NUM_PARC", data?.getStringExtra("NUM_PARC"))
        json.put("TIPO_PARC", data?.getStringExtra("TIPO_PARC"))
        json.put("VIA_ESTABELECIMENTO", data?.getStringExtra("VIA_ESTABELECIMENTO"))
        json.put("VIA_CLIENTE", data?.getStringExtra("VIA_CLIENTE"))
        return json.toString()
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (rbMsitef.isChecked) {
            var retornoSitef: RetornoMsiTef? = null
            try {
                retornoSitef = gson.fromJson(respSitefToJson(data), RetornoMsiTef::class.java)
            } catch (e: JSONException) {
                e.printStackTrace()
            }
            if (requestCode == REQ_CODE && resultCode == RESULT_OK) {
                if (retornoSitef?.codResp == "0") {
                    var impressao = ""
                    // Verifica se tem algo pra imprimir
                    if (!retornoSitef.textoImpressoCliente().isEmpty()) {
                        impressao += retornoSitef.textoImpressoCliente()
                    }
                    if (!retornoSitef.textoImpressoEstabelecimento().isEmpty()) {
                        impressao += "\n\n-----------------------------     \n"
                        impressao += retornoSitef.textoImpressoEstabelecimento()
                    }
                    if (!impressao.isEmpty()) {
                        dialogImpressaoGPOS(impressao, 17)
                    }
                }
                // Verifica se ocorreu um erro durante venda ou cancelamento
                if (acao == "venda" || acao == "cancelamento") {
                    if (retornoSitef?.codResp?.isEmpty() == true || retornoSitef?.codResp != "0" || retornoSitef?.codResp == null) {
                        dialodTransacaoNegadaMsitef(retornoSitef!!)
                    } else {
                        dialodTransacaoAprovadaMsitef(retornoSitef)
                    }
                }
            } else {
                // ocorreu um erro
                if (acao == "venda" || acao == "cancelamento") {
                    dialodTransacaoNegadaMsitef(retornoSitef!!)
                }
            }
            // Verifica se ocorreu erro na Ger7
        } else {
            if (resultCode == RESULT_OK && requestCode == REQ_CODE) {
                val retornoGer7 =
                    gson.fromJson(data?.getStringExtra("jsonResp"), RetornoGer7::class.java)
                // Verifica se tem algo pra imprimir
                if (retornoGer7.errmsg == null && retornoGer7.print != null) {
                    dialogImpressaoGPOS(retornoGer7.print, 17)
                }
                if (acao == "funcoes" && retornoGer7.errmsg != null) {
                    dialodTransacaoNegadaGer7(retornoGer7)
                }
                // Verifica se ocorreu um erro durante venda ou cancelamento
                if (acao == "venda" || acao == "cancelamento") {
                    if (retornoGer7.errmsg != null) {
                        dialodTransacaoNegadaGer7(retornoGer7)
                    } else {
                        dialodTransacaoAprovadaGer7(retornoGer7)
                    }
                }
            } else {
                val retornoGer7 =
                    gson.fromJson(data?.getStringExtra("jsonResp"), RetornoGer7::class.java)
                // ocorreu um erro durante venda ou cancelamento
                if (acao == "venda" || acao == "cancelamento") {
                    dialodTransacaoNegadaGer7(retornoGer7)
                }
            }
        }
    }

    fun validaIp(ipserver: String): Boolean {
        val p = Pattern.compile(
            "^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                    "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                    "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
                    "([01]?\\d\\d?|2[0-4]\\d|25[0-5])$"
        )
        val m = p.matcher(ipserver)
        val b = m.matches()
        return b
    }

    private fun maskTextEdits() {
        txtValorOperacao.addTextChangedListener(MoneyTextWatcher(txtValorOperacao))
    }

    private fun dialodTransacaoAprovadaMsitef(retornoMsiTef: RetornoMsiTef?) {
        val alertDialog = AlertDialog.Builder(this).create()
        val cupom = StringBuilder()
        cupom.append("CODRESP: ${retornoMsiTef?.codResp}\n")
        cupom.append("COMP_DADOS_CONF: ${retornoMsiTef?.compDadosConf}\n")
        cupom.append("CODTRANS: ${retornoMsiTef?.codTrans}\n")
        cupom.append("CODTRANS (Name): ${retornoMsiTef?.nameTransCod}\n")
        cupom.append("VLTROCO: ${retornoMsiTef?.getvlTroco()}\n")
        cupom.append("REDE_AUT: ${retornoMsiTef?.redeAut}\n")
        cupom.append("BANDEIRA: ${retornoMsiTef?.bandeira}\n")
        cupom.append("NSU_SITEF: ${retornoMsiTef?.nsuSitef}\n")
        cupom.append("NSU_HOST: ${retornoMsiTef?.nsuhost}\n")
        cupom.append("COD_AUTORIZACAO: ${retornoMsiTef?.codAutorizacao}\n")
        cupom.append("NUM_PARC: ${retornoMsiTef?.parcelas}\n")
        alertDialog.setTitle("Ação executada com sucesso")
        alertDialog.setMessage(cupom.toString())
        alertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "OK") { _, _ ->
            // Não existe nenhuma ação
        }
        alertDialog.show()
    }

    private fun dialogoErro(msg: String) {
        val alertDialog = AlertDialog.Builder(this).create()
        alertDialog.setTitle("Erro ao executar função")
        alertDialog.setMessage(msg)
        alertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "OK") { _, _ ->
            // Não existe nenhuma ação
        }
        alertDialog.show()
    }

    private fun dialodTransacaoAprovadaGer7(retorno: RetornoGer7) {
        val alertDialog = AlertDialog.Builder(this).create()
        val cupom = StringBuilder()
        cupom.append("version: ${retorno.version}\n")
        cupom.append("status: ${retorno.status}\n")
        cupom.append("config: ${retorno.config}\n")
        cupom.append("license: ${retorno.license}\n")
        cupom.append("terminal: ${retorno.terminal}\n")
        cupom.append("merchant: ${retorno.merchant}\n")
        cupom.append("id: ${retorno.id}\n")
        cupom.append("type: ${retorno.type}\n")
        cupom.append("product: ${retorno.product}\n")
        cupom.append("response: ${retorno.response}\n")
        cupom.append("authorization: ${retorno.authorization}\n")
        cupom.append("amount: ${retorno.amount}\n")
        cupom.append("installments: ${retorno.installments}\n")
        cupom.append("instmode: ${retorno.instmode}\n")
        cupom.append("stan: ${retorno.stan}\n")
        cupom.append("rrn: ${retorno.rrn}\n")
        cupom.append("time: ${retorno.time}\n")
        cupom.append("track2: ${retorno.track2}\n")
        cupom.append("aid: ${retorno.aid}\n")
        cupom.append("cardholder: ${retorno.cardholder}\n")
        cupom.append("prefname: ${retorno.prefname}\n")
        cupom.append("errcode: ${retorno.errcode}\n")
        cupom.append("label: ${retorno.label}\n")
        alertDialog.setTitle("Ação executada com sucesso")
        alertDialog.setMessage(cupom.toString())
        alertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "OK") { _, _ ->
            // Não existe nenhuma ação
        }
        alertDialog.show()
    }

    private fun dialodTransacaoNegadaMsitef(retornoMsiTef: RetornoMsiTef) {
        val alertDialog = AlertDialog.Builder(this).create()
        val cupom = StringBuilder()
        cupom.append("CODRESP: ${retornoMsiTef.codResp}")
        alertDialog.setTitle("Ocorreu um erro durante a realização da ação")
        alertDialog.setMessage(cupom.toString())
        alertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "OK") { _, _ ->
            // Não existe nenhuma ação
        }
        alertDialog.show()
    }

    private fun dialodTransacaoNegadaGer7(retorno: RetornoGer7) {
        val alertDialog = AlertDialog.Builder(this).create()
        val cupom = StringBuilder()
        cupom.append("version: ${retorno.version}\n")
        cupom.append("errcode: ${retorno.errcode}\n")
        cupom.append("errmsg: ${retorno.errmsg}\n")
        alertDialog.setTitle("Ocorreu um erro durante a realização da ação")
        alertDialog.setMessage(cupom.toString())
        alertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "OK") { _, _ ->
            // Não existe nenhuma ação
        }
        alertDialog.show()
    }

    fun ImprimaGer7(CupomTEF: String) {
        if (!CupomTEF.isEmpty()) {
            var curPos = 0
            var lastPos = 0
            while (curPos >= 0) {
                curPos = CupomTEF.indexOf("\n", curPos)
                if (curPos >= 0) {
                    try {
                        if (curPos != lastPos) {
                            tPRNTR.DrawString(this, iprntr!!, "CENTER", 10, 300, "NORMAL", true, false, false, 30, CupomTEF.substring(lastPos, curPos))
                        } else {
                            tPRNTR.DrawString(this, iprntr!!, "CENTER", 10, 300, "NORMAL", true, false, false, 30, "     ")
                        }
                        curPos++
                        lastPos = curPos
                    } catch (ex: Exception) {
                        // Lidar com a exceção, se necessário
                    }
                }
            }
        }
    }

    private fun dialogImpressaoGPOS(texto: String, size: Int) {
        val alertDialog = AlertDialog.Builder(this).create()
        val cupom = StringBuilder()
        cupom.append("Deseja realizar a impressão pela aplicação ?")
        alertDialog.setTitle("Realizar Impressão")
        alertDialog.setMessage(cupom.toString())
        alertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "Sim") { _, _ ->
            iprntr = iGedi?.getPRNTR()
            var textoEstabelecimento = ""
            var textoCliente = ""
            textoEstabelecimento = texto.substring(0, texto.indexOf("\n"))
            textoCliente = texto.substring(texto.indexOf("\n"))
            tPRNTR.DrawString(this, iprntr!!, "LEFT", 10, 2, "NORMAL", true, false, false, size, textoEstabelecimento)
            tPRNTR.DrawString(this, iprntr!!, "LEFT", 10, 2, "NORMAL", true, false, false, size, textoCliente)
            tPRNTR.DrawString(this, iprntr!!, "LEFT", 10, 2, "NORMAL", true, false, false, size, texto)
            try {
                iprntr?.DrawBlankLine(50)
                iprntr?.Output()
            } catch (e: GediException) {
                throw RuntimeException(e)
            }
        }
        alertDialog.setButton(AlertDialog.BUTTON_NEGATIVE, "Não") { _, _ ->
            // Não executa nada
        }
        alertDialog.show()
    }

    private fun execulteSTefVenda() {
        val intentSitef = Intent("br.com.softwareexpress.sitef.msitef.ACTIVITY_CLISITEF")
        intentSitef.putExtra("empresaSitef", "00000000")
        intentSitef.putExtra("enderecoSitef", txtIpServidor.text.toString().replace("\\s+".toRegex(), ""))
        intentSitef.putExtra("operador", "0001")
        intentSitef.putExtra("data", "20200324")
        intentSitef.putExtra("hora", "130358")
        intentSitef.putExtra("numeroCupom", op)
        intentSitef.putExtra("valor", Mask.unmask(txtValorOperacao.text.toString().trim()))
        intentSitef.putExtra("CNPJ_CPF", "03654119000176")
        intentSitef.putExtra("comExterna", "0")
        if (rbCredito.isChecked) {
            intentSitef.putExtra("modalidade", "3")
            if (txtParcelas.text.toString() == "0" || txtParcelas.text.toString() == "1") {
                intentSitef.putExtra("transacoesHabilitadas", "26")
            } else if (rbLoja.isChecked) {
                intentSitef.putExtra("transacoesHabilitadas", "27")
            } else if (rbAdm.isChecked) {
                intentSitef.putExtra("transacoesHabilitadas", "28")
            }
            intentSitef.putExtra("numParcelas", txtParcelas.text.toString())
        }
        if (rbDebito.isChecked) {
            intentSitef.putExtra("modalidade", "2")
            intentSitef.putExtra("transacoesHabilitadas", "16")
        }
        if (rbTodos.isChecked) {
            intentSitef.putExtra("modalidade", "0")
            intentSitef.putExtra("restricoes", "transacoesHabilitadas=16")
        }
        intentSitef.putExtra("isDoubleValidation", "0")
        intentSitef.putExtra("caminhoCertificadoCA", "ca_cert_perm")
        startActivityForResult(intentSitef, REQ_CODE)
    }

    private fun execulteSTefCancelamento() {
        val intentSitef = Intent("br.com.softwareexpress.sitef.msitef.ACTIVITY_CLISITEF")
        intentSitef.putExtra("empresaSitef", "00000000")
        intentSitef.putExtra("enderecoSitef", txtIpServidor.text.toString().replace("\\s+".toRegex(), ""))
        intentSitef.putExtra("operador", "0001")
        intentSitef.putExtra("data", currentDateTimeString)
        intentSitef.putExtra("hora", currentDateTimeStringT)
        intentSitef.putExtra("numeroCupom", op)
        intentSitef.putExtra("valor", Mask.unmask(txtValorOperacao.text.toString()))
        intentSitef.putExtra("CNPJ_CPF", "03654119000176")
        intentSitef.putExtra("comExterna", "0")
        intentSitef.putExtra("modalidade", "200")
        intentSitef.putExtra("isDoubleValidation", "0")
        intentSitef.putExtra("caminhoCertificadoCA", "ca_cert_perm")
        startActivityForResult(intentSitef, REQ_CODE)
    }

    private fun execulteSTefFuncoes() {
        val intentSitef = Intent("br.com.softwareexpress.sitef.msitef.ACTIVITY_CLISITEF")
        intentSitef.putExtra("empresaSitef", "00000000")
        intentSitef.putExtra("enderecoSitef", txtIpServidor.text.toString().replace("\\s+".toRegex(), ""))
        intentSitef.putExtra("operador", "0001")
        intentSitef.putExtra("data", currentDateTimeString)
        intentSitef.putExtra("hora", currentDateTimeStringT)
        intentSitef.putExtra("numeroCupom", op)
        intentSitef.putExtra("valor", Mask.unmask(txtValorOperacao.text.toString()))
        intentSitef.putExtra("CNPJ_CPF", "03654119000176")
        intentSitef.putExtra("comExterna", "0")
        intentSitef.putExtra("isDoubleValidation", "0")
        intentSitef.putExtra("caminhoCertificadoCA", "ca_cert_perm")
        intentSitef.putExtra("modalidade", "110")
        intentSitef.putExtra("restricoes", "transacoesHabilitadas=16;26;27")
        startActivityForResult(intentSitef, REQ_CODE)
    }

    private fun execulteSTefReimpressao() {
        val intentSitef = Intent("br.com.softwareexpress.sitef.msitef.ACTIVITY_CLISITEF")
        intentSitef.putExtra("empresaSitef", "00000000")
        intentSitef.putExtra("enderecoSitef", txtIpServidor.text.toString().replace("\\s+".toRegex(), ""))
        intentSitef.putExtra("operador", "0001")
        intentSitef.putExtra("data", "20200324")
        intentSitef.putExtra("hora", "130358")
        intentSitef.putExtra("numeroCupom", op)
        intentSitef.putExtra("valor", Mask.unmask(txtValorOperacao.text.toString()))
        intentSitef.putExtra("CNPJ_CPF", "03654119000176")
        intentSitef.putExtra("comExterna", "0")
        intentSitef.putExtra("modalidade", "114")
        intentSitef.putExtra("isDoubleValidation", "0")
        intentSitef.putExtra("caminhoCertificadoCA", "ca_cert_perm")
        startActivityForResult(intentSitef, REQ_CODE)
    }

    private fun execulteGer7Venda() {
        venda.type = GER7_VENDA
        venda.id = Random().nextInt(9999999).toString()
//        venda.amount = MaskGer7.unmask(txtValorOperacao.text.toString())
//        venda.installments = MaskGer7.unmask(txtParcelas.text.toString())
        if (rbDebito.isChecked) {
            venda.instmode = GER7_SEMPARCELAMENTO
        } else {
            if (venda.installments == "0" || venda.installments == "1") {
                venda.instmode = GER7_SEMPARCELAMENTO
            } else if (rbLoja.isChecked) {
                venda.instmode = GER7_PARCELADO_LOJA
            } else if (rbAdm.isChecked) {
                venda.instmode = GER7_PARCELADO_ADM
            }
        }
        venda.product = when {
            rbCredito.isChecked -> GER7_CREDITO
            rbDebito.isChecked -> GER7_DEBITO
            else -> GER7_VOUCHER
        }
        venda.receipt = if (cbImpressao.isChecked) GER7_HABILITA_IMPRESSAO else GER7_DESABILITA_IMPRESSAO
        venda.apiversion = GER7_API_VERSION
        val json = gson.toJson(venda)
        intentGer7.putExtra("jsonReq", json)
        startActivityForResult(intentGer7, REQ_CODE)
    }

    private fun execulteGer7Cancelamento() {
        venda.type = GER7_CANCELAMENTO
        venda.id = Random().nextInt(9999999).toString()
        venda.receipt = if (cbImpressao.isChecked) GER7_HABILITA_IMPRESSAO else GER7_DESABILITA_IMPRESSAO
        venda.apiversion = GER7_API_VERSION
        val json = gson.toJson(venda)
        intentGer7.putExtra("jsonReq", json)
        startActivityForResult(intentGer7, REQ_CODE)
    }

    private fun execulteGer7Funcoes() {
        venda.type = GER7_FUNCOES
        venda.id = Random().nextInt(9999999).toString()
        venda.receipt = if (cbImpressao.isChecked) GER7_HABILITA_IMPRESSAO else GER7_DESABILITA_IMPRESSAO
        venda.apiversion = GER7_API_VERSION
        val json = gson.toJson(venda)
        intentGer7.putExtra("jsonReq", json)
        startActivityForResult(intentGer7, REQ_CODE)
    }

    private fun execulteGer7Reimpressao() {
        venda.type = GER7_REIMPRESSAO
        venda.id = Random().nextInt(9999999).toString()
        venda.receipt = if (cbImpressao.isChecked) GER7_HABILITA_IMPRESSAO else GER7_DESABILITA_IMPRESSAO
        venda.apiversion = GER7_API_VERSION
        val json = gson.toJson(venda)
        intentGer7.putExtra("jsonReq", json)
        startActivityForResult(intentGer7, REQ_CODE)
    }


}