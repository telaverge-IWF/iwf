/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TYes extends Token
{
    public TYes()
    {
        super.setText("Y");
    }

    public TYes(int line, int pos)
    {
        super.setText("Y");
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TYes(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTYes(this);
    }

    public void setText(String text)
    {
        throw new RuntimeException("Cannot change TYes text.");
    }
}
