package io.github.linhelurking.meta_lang.parser

import io.github.linhelurking.meta_lang.MetaLangBaseVisitor
import io.github.linhelurking.meta_lang.MetaLangLexer
import io.github.linhelurking.meta_lang.MetaLangParser
import org.antlr.v4.runtime.tree.TerminalNode

class FormatVisitor : MetaLangBaseVisitor<MutableList<String>>() {
    override fun defaultResult(): MutableList<String> {
        return mutableListOf()
    }

    override fun aggregateResult(
        aggregate: MutableList<String>,
        nextResult: MutableList<String>
    ): MutableList<String> {
        aggregate.addAll(nextResult)
        return aggregate
    }

    // general case: direct text
    override fun visitTerminal(node: TerminalNode): MutableList<String> {
        val ret = mutableListOf<String>()
        if (node.symbol.type != MetaLangLexer.EOF) {
            ret.add(node.text)
        }
        return ret
    }

    override fun visitEol(ctx: MetaLangParser.EolContext?): MutableList<String> {
        val ret = mutableListOf<String>()
        ctx ?: return ret
        val iter = ctx.children.iterator()
        if (iter.hasNext()) {
            val first = iter.next()
            check(first is TerminalNode) {
                "First of eol should be terminal node!"
            }
            if (first.symbol.type != MetaLangLexer.SEMICOLON) {
                ret.add(";")
            }
            ret.add(first.symbol.text)
        }
        while (iter.hasNext()) {
            val next = iter.next()
            check(next is TerminalNode) {
                "Next of eol should be terminal node!"
            }
            ret.add(next.symbol.text)
        }
        return ret
    }

    private fun visitSpacedOp(ctx: MetaLangParser.ExprContext?, op: String): MutableList<String> {
        val ret = mutableListOf<String>()
        ctx ?: return ret
        check(ctx.children.size == 3) {
            "This rule should have only 3 children."
        }
        ret.addAll(ctx.children[0].accept(this))
        check(ctx.children[1] is TerminalNode)
        check((ctx.children[1] as TerminalNode).symbol.text == op)
        ret.add(" $op ")
        ret.addAll(ctx.children[2].accept(this))
        return ret
    }

    override fun visitMulExpr(ctx: MetaLangParser.MulExprContext?): MutableList<String> {
        return visitSpacedOp(ctx, "*")
    }

    override fun visitDivExpr(ctx: MetaLangParser.DivExprContext?): MutableList<String> {
        return visitSpacedOp(ctx, "/")
    }

    override fun visitAddExpr(ctx: MetaLangParser.AddExprContext?): MutableList<String> {
        return visitSpacedOp(ctx, "+")
    }

    override fun visitSubExpr(ctx: MetaLangParser.SubExprContext?): MutableList<String> {
        return visitSpacedOp(ctx, "-")
    }

    override fun visitAssignStat(ctx: MetaLangParser.AssignStatContext?): MutableList<String> {
        val ret = mutableListOf<String>()
        ctx ?: return ret
        check(ctx.children.size == 4)
        ret.addAll(ctx.children[0].accept(this))
        val assign = ctx.children[1]
        check(assign is TerminalNode)
        check(assign.symbol.text == "=")
        ret.add(" = ")
        ret.addAll(ctx.children[2].accept(this))
        ret.addAll(ctx.children[3].accept(this))
        return ret
    }
}