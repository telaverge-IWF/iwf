/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TEnumerated extends Token
{
    public TEnumerated()
    {
        super.setText("Enumerated");
    }

    public TEnumerated(int line, int pos)
    {
        super.setText("Enumerated");
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TEnumerated(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTEnumerated(this);
    }

    public void setText(String text)
    {
        throw new RuntimeException("Cannot change TEnumerated text.");
    }
}
