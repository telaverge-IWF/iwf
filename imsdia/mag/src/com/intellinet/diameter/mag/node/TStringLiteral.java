/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TStringLiteral extends Token
{
    public TStringLiteral(String text)
    {
        setText(text);
    }

    public TStringLiteral(String text, int line, int pos)
    {
        setText(text);
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TStringLiteral(getText(), getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTStringLiteral(this);
    }
}
