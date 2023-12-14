package io.github.linhelurking.meta_lang

import io.github.linhelurking.meta_lang.parser.FormatVisitor
import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream

fun main() {
    val bytes = "x=(1+2)*(3-4)\n".toByteArray() // + 0xFF.toByte()
    val lexer = MetaLangLexer(CharStreams.fromStream(bytes.inputStream()))
    val tokenStream = CommonTokenStream(lexer)
    val parser = MetaLangParser(tokenStream)
    val ctx = parser.prog()
//    println(ctx.text)
    val visitor = FormatVisitor()
    val res = ctx.accept(visitor).joinToString(separator = "")
    println(res)
}