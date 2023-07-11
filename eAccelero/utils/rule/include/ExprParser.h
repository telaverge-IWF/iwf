/*********************************-*-H-*-************************************
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
#ifndef __ExprParser_h__
#define __ExprParser_h__

#include <vector>
#include <iomanip>
#include <exception>
#include <sstream>
#include <string>

#include "Regexp.h"
#include "Ref.h"

/**
 * @file ExprParser.h
 * Refer @ref expr_parser "Expression parsing" for more information.
 */
 
/**@page expr_parser Expression Parsing
 * 
 * @section expr_parser_intro Expression Parser:
 *
 * Expression parser is used to used to parse the expressions of the form,
 * @code
 *      COMPARISON LOGICAL_OP COMPARISON LOGICAL_OP COMPARISON....
 * @endcode
 *
 * Paranthesis can be introduced to specify the precedence of the logical
 * operation.The possible Logcal operators are '&&' and '||'.
 * 
 * A comparison is of the following form,
 * @code
 *      VARIABLE RELATIONAL_OPERATOR CONSTANT/REGULAR_EXPRESSION
 * @endcode
 * 
 * Variables are generally the incoming messages, on which a condition is to be
 * checked. 
 *  - A CONSTANT as the name indicates is a constant value which can be an
 *    integer or a string
 *  - A string constant is enclosed within single quotes. It was decided to have
 *    single quotes because, in a json configuration, double quotes already has
 *    a meaning and though escapes can be used, it will not look legible.
 *  - A relational operation can be ==, !=, >=, >, <=, <
 * 
 * A sample expression looks like this
 * @code
 *  ( dia.Command-Code == 272 && dia.Origin-Host == 'node1.epc.3gppnetwork.org' )
 *     || ( dia.Application-Id != 4 && 
 *          dia.Origin-Realm = regex('^.*.epc.3gppnetwork.org$') )
 * @endcode
 *
 * @subsection expr_parser_op Operation:
 *
 * For the expression parser the input is a sequence of characters, which it
 * converts then into an expression tree.
 * @code
 * <char stream> --> [Lexer] -->  <tokens>  -->  [Parser]  --> <expr tree>
 * @endcode 
 * 
 * The tokenizer parsers the character stream and converts then into an list of
 * meaningful chunks called Tokens. The Parser feeds on the tokens and based on
 * the symbols and variables constructs an expression parse tree. For the expr
 * given above the parse tree looks like this
 * @code
 *                          +----------( || )------------+
 *                          |                            |
 *                +------( && )-----+          +------( && )------+
 *                |                 |          |                  |
 *           (CC == 272)  (OH == node1..)  (AppId != 4)   (OR == regex(..))
 * @endcode
 * 
 * After the parsing the variables and the constants are kept as strings. But
 * their types are identified (like var, int, string, or regex).   
 */


namespace eAccelero
{

/**
 * @class Token
 * @brief Represents a token formed from the character stream
 * 
 * This is a reference counted object, constructed by the Lexer and used by the
 * ExprParser. ExprParser uses the Tokens to construct the parse tree, based on
 * the token type. The leaf nodes in the expression tree are maintained as 
 * Tokens.
 */
class Token: public RefObj<>
{
 public:
    /**
     * @brief Token constructor accepting a c-style char
     * @param str       Token string
     * @param len       Length of the token string
     * @param tokenId   Type of the token
     * @param colNo     Column no. on which the token starts
     * @param lineNo    Line no. on which the token starts
     * 
     */
    Token(char *str, int len, int tokenId, int colNo = 0, int lineNo = 0)
        : m_token(str, len),
          m_tokenId(tokenId),
          m_colNo(colNo),
          m_line(lineNo)
    {
    }
    
    /**
     * @brief Token constructor accepting a c-style char
     * @param str       Token string
     * @param tokenId   Type of the token
     * @param colNo     Column no. on which the token starts
     * @param lineNo    Line no. on which the token starts
     * 
     */    
    Token(std::string& str, int tokenId, int colNo = 0, int lineNo = 0)
        : m_token(str),
          m_tokenId(tokenId),
          m_colNo(colNo),
          m_line(lineNo)
    {
    }

    std::string m_token;    /**< Token string */
    int m_tokenId;          /**< Token type */
    int m_colNo;            /**< Column number where token starts */
    int m_line;             /**< Line number where the token starts */
};

/**
 * Smart pointer for the Token. The reference couting is taken care internally
 * It is recommended to use TokenRef instead of a Token pointer.
 */
typedef Reference<Token> TokenRef;

/*
 * A table entry to define the tokens
 */
struct TokenDef
{
    const char *tokenStr;
    int id;
    int precedence;
};


/**
 * @class Lexer
 * @brief Converts the stream of characters to the predefined tokens.
 * 
 * The list of predefined tokens are determined by the Lexer::TokenType and the
 * token info are entered into the internal token definition table.The lexer 
 * streams through the character seqeunce and if a predefined token is found, it
 * adds it to its list. Once all the tokens are extracted, the ExprParser, uses
 * the lexer, extract Tokens one by one and form the expression tree.
 *  
 */
class Lexer
{
 public:
    /**
     * Defines the type of token. Tokens are divided into 4 sections
     *  - Basic
     *  - Symbols
     *  - Identifiers/keywords
     *  - Regular expressions
     */
    enum TokenType
    {
        TOK_EOF,                        // 0 Basic tokens
        TOK_LITERAL,                    // 1

        TOK_SYM_START,                  // 2 Symbols starts here
        TOK_L_PAREN = TOK_SYM_START,    // 2
        TOK_R_PAREN,                    // 3
        TOK_AND,                        // 4
        TOK_OR,                         // 5
        TOK_LTE,                        // 6
        TOK_LT,                         // 7
        TOK_EQ,                         // 8
        TOK_NEQ,                        // 9
        TOK_GTE,                        // 10
        TOK_GT,                         // 11
        TOK_SEM,                        // 12
        TOK_SQUOTE,                     // 13
        TOK_SYM_END = TOK_SQUOTE,       // 13

        TOK_IDEN_START,                 // 14 Keywords starts here
        TOK_SUBSTR = TOK_IDEN_START,    // 14
        TOK_IDEN_END = TOK_SUBSTR,      // 14

        TOK_REGEX_START,                // 15 Reg expression tokens start here
        TOK_REGEX = TOK_REGEX_START,    // 15
        TOK_DIGIT,                      // 16
        TOK_SQUOTE_STR,                 // 17
        TOK_REGEX_END = TOK_SQUOTE_STR, // 17

        TOK_MAX                         // 18
    };

    
    /**
     * @brief Constructor for the lexer.
     * 
     * Initializes the internal data structures.
     */
    Lexer();
    
    /**
     * @brief Desctructor fo the lexer.
     */
    ~Lexer();

    /**
     * @brief Extracts seqence of tokens from the character stream
     * @param str   Character stream to be tokenized
     * @return Returns the number of tokens parsed
     * 
     * This extracts the tokens and maintains them in an internal list
     * To extract tokens use Lookahead() and GetNextToken().
     * 
     * Algorithm:
     *  - Skip white spaces
     *  - Look for a regular expression match
     *  - else check if string starts with a symbol or identifier
     *  - else consider it as a literal string
     *  - store the identified token into the list
     *  - and repeate the procedure till no more chars to scan
     */
    int Tokenize(char *str);


    /**
     * @brief Looks ahead by one token in the token stream
     * @return Returns the type of the token that is ahead
     * 
     * While parsing the tokens this will be used to see what is the next token
     * to make decisions on the current token. Use in conjuntion with 
     * GetNextToken()
     * 
     */
    int Lookahead()
    {
        if (m_curTokenIdx == m_tokens.size())
        {
            return TOK_EOF;
        }
        return m_tokens[m_curTokenIdx]->m_tokenId;
    }
    
    
    /**
     * @brief Returns the next token in the token stream
     * @return Returns the token reference
     * 
     * Once all the tokens are parsed, invoke Reset() to loop through the tokens
     * again.
     */
    TokenRef GetNextToken()
    {
        if (m_curTokenIdx == m_tokens.size())
        {
            return NULL;
        }
        return m_tokens[m_curTokenIdx++];
    }


    /**
     * @brief Resets the token stream pointer to the beginning of the stream
     * @see   Lexer::GetNextToken()
     */
    void Reset()
    {
        m_curTokenIdx = 0;
    }


    /**
     * @brief Given the token type, provides the string equivalent
     * @param tokId     Token Type of the token to be converted to string
     * @return Returns the string equivalent of the token type
     */
    static const char* GetSymbol(int tokId)
    {
        return m_tokenDefs[tokId].tokenStr;
    }
    
    /**
     * @brief Given the token type, returns the precedence of the token
     * @param tokId
     * @return Retursn the precedence of the token
     */
    static int Precedence(int tokId)
    {
        return m_tokenDefs[tokId].precedence;
    }

 protected:
    
    /**
     * @brief Provides the number of leading white space characters in str
     * @param str   String from which number of leading white space info to be
     *              extracted.
     * @return Number of white space characters ahead
     * 
     * Used to skip the white space characters in the character stream.
     */
    int GetWS(char *str);
    
    
    /**
     * @brief Extracts a word from the character stream
     * @param str   character stream
     * @return Returns the number of characters in the word
     * 
     * A word anything that is not a symbol or a whitespace.
     */
    int GetWord(char *str);


    /**
     * @brief Checks if the char sequence starts with a string
     * @param str   character stream
     * @return Number of characters in the symbol, 0 if no symbol is found
     */
    int IsSymbol(char *str);
    
    /**
     * @brief Checks if the char sequence `str` starts with `substr`
     * @param str   character stream
     * @param subStr
     * @return 
     */
    int StartsWith(char *str, const char *subStr);
    
    std::vector<TokenRef> m_tokens; /**< List of tokens extracted by the lexer*/
    
    unsigned m_curTokenIdx;         /**< Current token index in the list, 
                                     * when the parser is invoked */
                                     
    unsigned m_curLine;             /**< Current line during lexing */
    
    unsigned m_curCol;              /**< Current column position during lexing */

    /** Predefined table of token definitions */
    static TokenDef m_tokenDefs[TOK_MAX];   

    typedef std::vector<Regexp*> RegexTable;
    RegexTable m_regexTable;    /**< Table for regular expression Tokens */
};


/**
 * @brief Given the tokenId returns if it is a logical operator or not
 * @param tokId
 * @return True if the token is logical, false otherwise
 */
inline bool IsLogical(int tokId)
{
    return (tokId == Lexer::TOK_AND || tokId == Lexer::TOK_OR);
}

/**
 * @brief Given the tokenId returns if the token is a relational operator
 * @param tokId
 * @return True if the token is relational, false otherwise
 */
inline bool IsComparison(int tokId)
{
    return (tokId >= Lexer::TOK_LTE && tokId <= Lexer::TOK_GT) 
            || tokId == Lexer::TOK_REGEX;
}

// Forward declaration to define the ExprRef type, which is used inside the 
// Expr class
class Expr;

/** 
 * Smart pointer to the Expr pointer object. Since Expr is referene counted it
 * is recommend to use the ExprRef instead of a pointer to Expr
 */
typedef Reference<Expr> ExprRef;

/**
 * @class Expr
 * @brief Encapsualtion for an expression object
 * 
 * An expression can be one of the following
 *  - token
 *  - a relational operation involving two tokens and a logical operator
 *  - a logical operation involving two expressions and a logical operator
 * 
 * This definition makes Expr a recursive object. This helps in forming the 
 * expression tree easier. The whole expression tree is represented as an 
 * expression containing, multiple other nested expressions and this goes
 * all the way down, until a Token a reached.
 * 
 * Expr is a reference counted object.
 */
class Expr: public RefObj<>
{
 public:

    /**
     * Semantics of the parsed Token, different from Lexer::TokenType
     */
    enum TokenType
    {
        TypeNone,
        TypeInt,
        TypeString,
        TypeRegex,
        TypeVar,
    };

    /**
     * @brief Constructor to construct an expression from a token
     * @param tok   Parsed token
     * @param type  Semantics of the token
     * 
     * This variant of the constructor is used when a variable/constant is
     * encountered
     */
    Expr(TokenRef tok = NULL, TokenType type = TypeVar)
        : m_op(Lexer::TOK_EOF),
          m_lhs(NULL),
          m_rhs(NULL),
          m_token(tok),
          m_type(type)
    {
    }

    
    /**
     * @brief Construct an expression from two other sub expressions
     * @param lhs   Left hand side expression
     * @param rhs   Right hand side expression
     * @param op    Operator between the LHS and RHS
     * 
     * This variant is used to construct an expression from an expression
     */
    Expr(ExprRef &lhs, ExprRef &rhs, int op)
        : m_op(op),
          m_lhs(lhs),
          m_rhs(rhs),
          m_token(NULL)
    {
    }

    /**
     * @brief Expression destructor
     */
    ~Expr()
    {
    }

    int  m_op;          /**< Operator of the expression */
    ExprRef m_lhs;      /**< LHS sub-expression within this expression */
    ExprRef m_rhs;      /**< RHS sub-expression within this expression */
    TokenRef m_token;   /**< If this is set, then this the leaf node */
    TokenType m_type;   /**< Semantics of the parsed token */

    // Utility function to print the expression in a s-expr format
    static void Print(ExprRef &expr, int indent = 0);
    
    // Utility function to pringthe expressio in a post fix format
    // Post order traversal of the expression tree
    static int PostFixPrint(ExprRef &expr);
};


/**
 * @class ParserException
 * @brief Exception when the expression parser encounters and error
 * @see Lexer, ExprParser
 */
class ParserException: public Exception
{
 public:
    /**
     * @brief Constructor to create the parser exception
     * @param str   Error description
     * @param tok   Token on which the error is encountered
     */
    ParserException(const char *str, TokenRef tok = NULL)
        : Exception(str)
    {
        std::stringstream  ss;
        ss << "Parser Exception: <" << str << ">";
        if (tok)
        {
            ss << " Token'" << tok->m_token << "' at line " << tok->m_line+1 
                                            << ":"          << tok->m_colNo+1;
        }
        m_excStr = ss.str();
    }
    
    /**
     * @brief Destructor for parser exception
     */
    virtual ~ParserException() throw() {}
    

    /**
     * @brief Overridden function to print the exception string
     * @return Exception string
     */
    virtual const char* what() const throw()
    {
        return m_excStr.c_str();
    }
 protected:
    std::string m_excStr;   /**< Exception string */
};

/**
 * @class ExprParser
 * @brief Parser used to parse the expression string
 * 
 * The input for the expression parser is the list of tokens and the output
 * is the expression tree. The parser is implemented as a LL(1) recursive
 * descent parser.
 */
class ExprParser
{
 public:
 
    /** State of the expression parser while parsing tokens */
    enum State
    {
        Init,
        Comparison,  // <, >, == etc..
        Logical,     // && || 
    };

    /**
     * @brief Constructor
     */
    ExprParser()
        : m_lexer(NULL),
          m_state(Init),
          m_curTok(NULL),
          m_parenCount(0)
    {
    }

    /**
     * @brief Parses the stream of tokens and constructs an expression tree
     * @param lexer Lexer object, with the extracted tokens
     * @return Returns and expression object, which contains other expressions
     * 
     * The parser is implemented as a LL(1) Recursive descent parser
     */
    ExprRef Parse(Lexer *lexer);

 protected:

    /**
     * @brief Performs a recursive descent on the token stream and constructs parse tree
     * @param p   The precedence of the previous operator/symbol
     * @return The constructed expression tree
     * 
     * Parse tokens one by one. If a symbol with more precedence is encountered,
     * then descend into the recursion to build the tree. When the precedence of
     * the next symbol is less, than the current recursion's precedence,
     * then ascend. This creates the expresison in a tree form.
     */
    ExprRef RecursiveDescent(int p = 0);
    
    
    /**
     * @brief Parse the tokens for comparison tokens 
     * @return Expression for the comparison having lhs rhs and operation
     */
    ExprRef ParseComparison();
    
    /**
     * @brief Parse the logical expression
     * @param lhs - Left hand side of the logcal expression
     * @return The completed constructed parse tree for the logical expression
     * 
     * Does a recursive descent and extract the rhs expression, then with the 
     * current expression extracted so far as lhs, a new expression is formed.
     */
    ExprRef ParseLogical(ExprRef &lhs);

    /** Lexer object that contains the tokens */
    Lexer* m_lexer;
    
    /** Current state of the parser, what it has parsed, what it is expecting*/
    State  m_state;
    
    /** The current token that is being parsed */
    TokenRef  m_curTok;

    /** 
     *  Number of paranthesis encounter. Will be incremented on getting a '(
     *  and decremented on a ')'
     */
    int m_parenCount;
};

}

#endif // __ExprParser_h__
