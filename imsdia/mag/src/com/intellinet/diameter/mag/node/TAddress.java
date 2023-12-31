/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TAddress extends Token
{
    public TAddress()
    {
        super.setText("Address");
    }

    public TAddress(int line, int pos)
    {
        super.setText("Address");
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TAddress(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTAddress(this);
    }

    public void setText(String text)
    {
        throw new RuntimeException("Cannot change TAddress text.");
    }
}
