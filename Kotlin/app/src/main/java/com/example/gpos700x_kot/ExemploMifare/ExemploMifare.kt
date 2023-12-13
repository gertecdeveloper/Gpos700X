package com.example.gpos700x_kot.ExemploMifare

import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import br.com.gertec.easylayer.contactless.AuthenticationException
import br.com.gertec.easylayer.contactless.ConnectionException
import br.com.gertec.easylayer.contactless.GenericContactLess
import br.com.gertec.easylayer.contactless.MifareClassic
import br.com.gertec.gedi.GEDI
import com.example.gpos700x_kot.R
import com.example.gpos700x_kot.Utils
import java.io.IOException

class ExemploMifare : AppCompatActivity() {

    private lateinit var utils: Utils
    private lateinit var outputView: TextView
    private lateinit var readBlocksText: TextView
    private lateinit var authenticationKeyText: TextView
    private lateinit var mifare: MifareClassic
    private val DEFAULT_BLOCKS_TO_WRITE = 64
    private val DEFAULT_DATA_VALUE_INDEX = 5
    private val DEFAULT_RESTORE_INDEX = 6
    private val BLOCKS_IN_SECTOR = 4

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.mifare)

        GEDI.init(this)
        utils = Utils()
        outputView = findViewById(R.id.outputView)
        authenticationKeyText = findViewById(R.id.authenticationKeyText)
        readBlocksText = findViewById(R.id.readBlocksText)
    }


    fun onReadBlocks(view: View) {
        var blocksToRead = readBlocksText.text.toString().toInt()
        blocksToRead = if (blocksToRead > 64) 64 else blocksToRead
        val authenticationKey = utils.hexStringToByteArray(authenticationKeyText.text.toString())
        readBlocks(blocksToRead, authenticationKey)
    }

    private fun readBlocks(blocksToRead: Int, authenticationKey: ByteArray) {
        mifare = MifareClassic()
        var cardId: ByteArray
        val cardData = Array(blocksToRead) { ByteArray(MifareClassic.BLOCK_SIZE) }

        try {
            cardId = mifare.connect(100000)
            for (blockIndex in 0 until blocksToRead) {
                if (blockIndex % BLOCKS_IN_SECTOR == 0) {
                    val sector = mifare.blockToSector(blockIndex)
                    mifare.authenticateSectorWithKeyA(sector, authenticationKey)
                }
                cardData[blockIndex] = mifare.readBlock(blockIndex)
            }
            mifare.close()
            showCardData(cardId, cardData)
        } catch (e: ConnectionException) {
            showError(e.message)
            e.printStackTrace()
        } catch (e: AuthenticationException) {
            showError(e.message)
            e.printStackTrace()
        } catch (e: IOException) {
            showError(e.message)
            e.printStackTrace()
        }
    }

    private fun showCardData(cardId: ByteArray, cardData: Array<ByteArray>) {
        outputView.text = "Card id: " + utils.byteArrayToHexString(cardId) + "\n"
        for (blockIndex in cardData.indices) {
            outputView.append("Block [$blockIndex] : " + utils.byteArrayToHexString(cardData[blockIndex]) + "\n")
            outputView.append("Block [$blockIndex] : " + String(cardData[blockIndex]) + "\n")
        }
    }

    fun onSendCommand(view: View) {
        val cardInterface = GenericContactLess()

        // This command has been copied from Gedi_Cl test case (commandSendTest) from GEDI lib
        val cmdData = byteArrayOf(
            0x00, 0xa4.toByte(), 0x04, 0x00, 0x0e, 0x32, 0x50, 0x41, 0x59, 0x2e, 0x53, 0x59, 0x53, 0x2e, 0x44, 0x44, 0x46,
            0x30, 0x31, 0x00
        )
        var cmdResp: ByteArray? = null

        try {
            cardInterface.connect(2000)

            // TODO validate expected 'cmdResp' response
            cmdResp = cardInterface.sendCommand(cmdData)

            cardInterface.close()
        } catch (e: ConnectionException) {
            showError(e.message)
        } catch (e: IOException) {
            showError(e.message)
        }
    }

    private fun showError(message: String?) {
        outputView.text = "Error : $message"
    }

}