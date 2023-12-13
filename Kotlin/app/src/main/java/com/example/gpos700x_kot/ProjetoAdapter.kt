package com.example.gpos700x_kot

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ImageView
import android.widget.TextView

class ProjetoAdapter(context: Context, resource: Int, projetos: List<Projeto>) :
    ArrayAdapter<Projeto>(context, resource, projetos) {

    private val projetoList: List<Projeto> = projetos

    override fun getView(position: Int, convertView: View?, parent: ViewGroup): View {
        var v = convertView
        if (v == null) {
            val ctx = context
            val vi = ctx.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater
            v = vi.inflate(R.layout.listprojetos, null)
        }
        val projeto = projetoList[position]

        if (projeto != null) {
            v!!.findViewById<TextView>(R.id.txtProjeto).text = projeto.nome
            v.findViewById<ImageView>(R.id.imgIcon).setImageResource(projeto.img)
        }
        return v!!
    }
}
