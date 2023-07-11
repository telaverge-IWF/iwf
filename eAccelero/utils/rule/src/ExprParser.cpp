/*********************************-*CPP*-************************************
 *                                                                          *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************/
 
#include <iostream>
#include <iomanip>
#include <string.h>

#include "ExprParser.h"

namespace eAccelero
{

// Any token definition goes here. The last column is the precendence
TokenDef Lexer::m_tokenDefs[Lexer::TOK_MAX] = 
{
    // basic
    { "EOF", Lexer::TOK_EOF, 0},              // 0
    { "Literal", Lexer::TOK_LITERAL, 1},      // 1

    // symbols
    { "(", Lexer::TOK_L_PAREN, 1 },            // 2
    { ")", Lexer::TOK_R_PAREN, 1 },            // 3
    { "&&", Lexer::TOK_AND, 2 },               // 4
    { "||", Lexer::TOK_OR, 2 },                // 5
    { "<=", Lexer::TOK_LTE, 3 },               // 6
    { "<", Lexer::TOK_LT, 3 },                 // 7
    { "==", Lexer::TOK_EQ, 3 },                // 8
    { "!=", Lexer::TOK_NEQ, 3},                // 9 
    { ">=", Lexer::TOK_GTE, 3 },               // 10
    { ">", Lexer::TOK_GT, 3},                  // 11
    { ";", Lexer::TOK_SEM, 1},                 // 12
    { "'", Lexer::TOK_SQUOTE, 4},              // 13

    // identifiers
    {"substr", Lexer::TOK_SUBSTR, 3},          // 14

    // Regular expressions
    {"^regex\\('([^']+)'\\)", Lexer::TOK_REGEX, 1},  // 15
    {"^\\d+", Lexer::TOK_DIGIT, 1},                  // 16
    {"^'([^']+)'", Lexer::TOK_SQUOTE_STR, 1}         // 17
};

Lexer::Lexer()
    : m_curTokenIdx(0),
      m_curLine(0),
      m_curCol(0)
{
    for (int i = TOK_REGEX_START; i <= TOK_REGEX_END; i++)
    {
        m_regexTable.push_back(new Regexp(m_tokenDefs[i].tokenStr));
    }
}

Lexer::~Lexer()
{
    for (RegexTable::iterator rit = m_regexTable.begin();
            rit != m_regexTable.end();)
    {
        delete *rit;
        rit = m_regexTable.erase(rit);
    }
}

int Lexer::Tokenize(char *str)
{
    int len = 0;
    int tokId = 0;
    int i = 0;
    int ret = 0;
    int remLen = strlen(str);
    bool noMatch = true;
    MatchList matches;

    while(*str)
    {
        // Skip whitespace
        len = GetWS(str);
        str += len;
        remLen -= len;
        if (str[0] == '\0')
        {
            break;
        }

        // first match for the regular expressions
        for (i = TOK_REGEX_START; i <= TOK_REGEX_END; i++)
        {
            ret = m_regexTable[i - TOK_REGEX_START]->Match(str, remLen, matches);
            if (ret > 0)
            {
                tokId = i;
                noMatch = false;
                break;
            }
        }
        if (!noMatch)
        {
            i = (matches.size() > 1) ? 1: 0;
            TokenRef tok = new Token(matches[i].matchStr, tokId, m_curCol, m_curLine);
            m_tokens.push_back(tok);

            len = matches[0].end;

            str += len;
            m_curCol += len;
            remLen -= len;
            noMatch = true;
            continue;
        }

        // then for symbols and identifiers
        for (i = TOK_SYM_START; i < TOK_REGEX_START; i++)
        {
            len = StartsWith(str, m_tokenDefs[i].tokenStr);
            if (len)
            {
                // token match
                tokId = m_tokenDefs[i].id;
                noMatch = false;
                break;
            }
        }

        if (noMatch)
        {
            // Not a regex match or a symbol match. Store it as a literal
            len = GetWord(str);
            tokId = TOK_LITERAL;
        }

        TokenRef tok = new Token(str, len, tokId, m_curCol, m_curLine);
        m_tokens.push_back(tok);

        str += len;
        m_curCol += len;
        remLen -= len;
        noMatch = true;
    }

    return m_tokens.size();
}


int Lexer::GetWS(char *str)
{
    int ret = 0;
    while((*str != '\0') && isspace(*str))
    { 
        str++; ret++; m_curCol++;
        if (*str == '\n')
        {
            m_curLine++;
            m_curCol = 0;
            str++; ret++;
        }
    }
    return ret;
}

int Lexer::GetWord(char *str)
{
    int ret = 0;
    while( *str && !isspace(*str) && !IsSymbol(str) )
    { 
        str++; ret++;
    }
    return ret;
}

int Lexer::IsSymbol(char *str)
{
    int i = 0, len = 0;
    for (i = TOK_SYM_START; i <= TOK_SYM_END; i++)
    {
        len = StartsWith(str, m_tokenDefs[i].tokenStr);
        if (len)
        {
            // token match
            break;
        }
    }
    return len;
}

int Lexer::StartsWith(char *str, const char *subStr)
{
    int i = 0;
    for (i = 0; str[i] != 0 && subStr[i] != 0; i++)
    {
        if (str[i] != subStr[i])
        {
            break;
        }
    }
    if (subStr[i] == 0)
    {
        // Match found
        return i;
    }
    return 0;
}

void Expr::Print(ExprRef &expr, int indent)
{
    if (expr->m_token)
    {
        std::cout << std::setw(indent) << expr->m_token->m_token;
        return;
    }
    std::cout << "( " << Lexer::GetSymbol(expr->m_op) << " , ";
    Print(expr->m_lhs);
    std::cout << ", ";
    Print(expr->m_rhs);
    std::cout << " ) ";
}

int Expr::PostFixPrint(ExprRef &expr)
{
    static int counter = 0;
    int retLHS = 0;
    int retRHS = 0;
    if (IsComparison(expr->m_op))
    {
        std::cout << counter << ". " << expr->m_lhs->m_token->m_token << " "
                  << Lexer::GetSymbol(expr->m_op) << " "
                  << expr->m_rhs->m_token->m_token << std::endl;
        return counter++;
    }
    retLHS = PostFixPrint(expr->m_lhs);
    retRHS = PostFixPrint(expr->m_rhs);
    std::cout << counter << ". $" << retLHS << " " 
              << Lexer::GetSymbol(expr->m_op) << " "
              << "$" << retRHS << std::endl;
    return counter++;
}

// LL(1) recursive desent parser
ExprRef ExprParser::Parse(Lexer *lexer)
{
    m_lexer = lexer;

    m_lexer->Reset();

    ExprRef retExpr = this->RecursiveDescent();
    if (m_parenCount)
    {
        throw ParserException("Mismatching paranthesis");
    }

    return retExpr;
}

ExprRef ExprParser::RecursiveDescent(int p)
{
    ExprRef retExpr;
    bool quit = false;
    
    // Parse tokens one by one. If a symbol with more precedence is encountered,
    // then descend into the recursion to build the tree. When the precedence of 
    // the next symbol is less, than the current recursion's precedence,
    // then ascend. This creates the expresison in a tree form.
    m_curTok = m_lexer->GetNextToken();
    while(m_curTok && !quit)
    {
        switch (m_curTok->m_tokenId)
        {
            case Lexer::TOK_L_PAREN:
                m_parenCount++;
                retExpr = this->RecursiveDescent(Lexer::Precedence(Lexer::TOK_L_PAREN));

                // Consume the right paranthesis
                if (m_lexer->Lookahead() != Lexer::TOK_R_PAREN)
                {
                    throw ParserException("Expected Symbol after", m_curTok);
                }
                m_curTok = m_lexer->GetNextToken();
                m_parenCount--;

                break;

            case Lexer::TOK_LITERAL:
                // If the current token is literal, only comparison is possible
                retExpr = this->ParseComparison();
                break;
            case Lexer::TOK_AND:
            case Lexer::TOK_OR:
                // If the token is a logical operation, then having the computed 
                // expression so far as the LHS, parse the RHS. This returns an
                // expresison with LHS and RHS 
                 retExpr = this->ParseLogical(retExpr);
                break;
            default:
                // No other tokens are epected
                throw ParserException("Unexpected token", m_curTok);
        }

        if (Lexer::Precedence(m_lexer->Lookahead()) <= p)
        {
            // Exit condition for the recursion. If the precednece of the next 
            // operator is less, then go back to the previous recursion layer.
            // This will never be hit for the first call to this function as the
            // precedence is 0
            quit = true;
        }
        else
        {
            m_curTok = m_lexer->GetNextToken();
        }
    }
    return retExpr;
}

// Comparison is of the form -> lhs COMP-OP rhs 
//      a == b, a != b, a >= b etc
ExprRef ExprParser::ParseComparison()
{
    // Form the LHS
    ExprRef lhs = new Expr(m_curTok);

    // Get the operator
    m_curTok = m_lexer->GetNextToken();
    if (!IsComparison(m_curTok->m_tokenId))
    {
        throw ParserException("Comparison operator expected", m_curTok);
    }
    int op = m_curTok->m_tokenId;
    Expr::TokenType type = Expr::TypeNone;
    TokenRef rhsTok;

    // Get the RHS. RHS can be a string or an integer or another var
    m_curTok = m_lexer->GetNextToken();
    switch(m_curTok->m_tokenId)
    {
        case Lexer::TOK_SQUOTE_STR:
            rhsTok = m_curTok;
            type = Expr::TypeString;
            break;
        case Lexer::TOK_REGEX:
            rhsTok = m_curTok;
            type = Expr::TypeRegex;
            op = Lexer::TOK_REGEX; // change the operation to pattern match
            break;
        case Lexer::TOK_LITERAL:
            type = Expr::TypeVar;
            rhsTok = m_curTok;
            break;
        case Lexer::TOK_DIGIT:
            type = Expr::TypeInt;
            rhsTok = m_curTok;
            break;
        default:
            throw ParserException("Unexpected RHS token", m_curTok);
    }

    ExprRef rhs = new Expr(rhsTok, type);

    // Form the comparison expression
    ExprRef compExpr = new Expr(lhs, rhs, op);

    return compExpr;
}

ExprRef ExprParser::ParseLogical(ExprRef &lhs)
{
    if (!IsLogical(m_curTok->m_tokenId))
    {
        throw ParserException("Logical operator expected", m_curTok);
    }
    int op = m_curTok->m_tokenId;

    // Do a recursive descent and extract the rhs expression, then with the 
    // current expression extracted so far as lhs, form a new expression
    ExprRef rhs = this->RecursiveDescent(Lexer::Precedence(op));
    ExprRef retExpr = new Expr(lhs, rhs, op);

    return retExpr;
}

} // namespace eAccelero

// Sample code for token generation and expression parsing. Don't remove
#if 0
int main()
{
    Lexer lex;
    //char* exprStr = (char*)("  hello==test && abc <= 123 || xyz>456");
    char* exprStr = (char*)(
"(a == regex('abc') || a != 'hello') && ((b > d || b <= e) || (d >= c && d < a))");

    std::cout << "Expr: " << exprStr << "\n\n";

    int num = lex.Tokenize(exprStr);

    std::cout << "Tokens returned = " << num << std::endl;

    TokenRef tok;
    while (lex.Lookahead() != Lexer::TOK_EOF)
    {
        tok = lex.GetNextToken();
        std::cout << "Token Type: " << tok->m_tokenId 
                  << " Token: " << tok->m_token << " "
                  <<  tok->m_line+1 << ":" << tok->m_colNo+1 <<std::endl;
    }

    lex.Reset();

    ExprParser parser;
    ExprRef expr = parser.Parse(&lex);

    Expr::Print(expr);
    std::cout << std::endl;

    Expr::PostFixPrint(expr);

    delete expr;

    return 0;
}
#endif
