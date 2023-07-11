/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TDiameterId extends Token
{
    public TDiameterId()
    {
        super.setText("DiamIdent");
    }

    public TDiameterId(int line, int pos)
    {
        super.setText("DiamIdent");
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TDiameterId(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTDiameterId(this);
    }

    public void setText(String text)
    {
        throw new RuntimeException("Cannot change TDiameterId text.");
    }
}
