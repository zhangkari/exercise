package com.org;

import java.util.List;
import java.util.LinkedList;

public class SenderRadar implements ISender
{
	private List<IReceiver> mReceiverList;

	public SenderRadar()
	{
		mReceiverList = new LinkedList();	
	}

	public void send(RadarSignal signal)
	{
		for(IReceiver receiver : mReceiverList)
		{
			if(null != receiver)
			{
				receiver.onReceive(signal);
			}
		}
	}

	public void addReceiver(IReceiver receiver)
	{
		mReceiverList.add(receiver);
	}

	public void removeReceiver(IReceiver receiver)
	{
		mReceiverList.remove(receiver);
	}
}
