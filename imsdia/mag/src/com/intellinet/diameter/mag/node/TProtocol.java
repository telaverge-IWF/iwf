/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TProtocol extends Token
{
    public TProtocol()
    {
        super.setText("protocol");
    }

    public TProtocol(int line, int pos)
    {
        super.setText("protocol");
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TProtocol(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTProtocol(this);
    }

    public void setText(String text)
    {
        throw new RuntimeException("Cannot change TProtocol text.");
    }
}
