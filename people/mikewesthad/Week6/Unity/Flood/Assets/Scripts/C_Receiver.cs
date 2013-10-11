using UnityEngine;
using System.Collections;

public class C_Receiver : MonoBehaviour {

	//You can set these variables in the scene because they are public 
	public string RemoteIP = "127.0.0.1";
	public int SendToPort  = 57131;
	public int ListenerPort  = 57130;
	
	
	public bool led1Connected = true;
	public bool led2Connected = true;
	public bool led1On = true;
	public bool led2On = true;
	
	private bool wasLed1On = true;
	private bool wasLed2On = true;
	private bool hasLedStatusChanged = true;
	private int numberChangeSignals = 5;
	private int currentChangeSignal = 0;
	
	//REMEMBER!!
	// You must have unity set to run in background (build settings)
	// or you cant have it listening when you have pd foregrounded
	//
	// Also, all callbacks are on a thread so you cant use them to 
	// directly modify Unity core, like transforms etc
	// instead mark a flag or value
	// then check this in your update loop
	
	private Osc handler;

//////////////////////////////////////////////////////////////////// 
	void Start () {

		//Initializes on start up to listen for messages
		//make sure this game object has both UDPPackIO and OSC script attached
		
		UDPPacketIO udp = GetComponent<UDPPacketIO>();
		udp.init(RemoteIP, SendToPort, ListenerPort);
			
		handler = GetComponent<Osc>();
		handler.init(udp);
				
		handler.SetAddressHandler("/arduino/state", arduinoHandler);	
	}
	
////////////////////////////////////////////////////////////////////	
	//explicitly gets osc parameter value as an INT
	//Have ot do this since the incoming messages arent typed, or you might want a conversion
	public int GetAsInt(OscMessage oscMessage,int which)
	{
		
		if(oscMessage.Values[which].GetType()==typeof(int))return (int)oscMessage.Values[which];
		
		if(oscMessage.Values[which].GetType()==typeof(float))
		{
			float temp=(float)oscMessage.Values[which];
			int ret=(int)temp;
			return ret;
		}

		return 0;
		
	}
////////////////////////////////////////////////////////////////////
	//explicitly gets osc parameter value as a FLOAT
	public float GetAsFloat(OscMessage oscMessage,int which)
	{
		
		if(oscMessage.Values[which].GetType()==typeof(float))
		{
			return (float)oscMessage.Values[which];
			
		}
		
		if(oscMessage.Values[which].GetType()==typeof(int))
		{
			int temp=(int)oscMessage.Values[which];
			float ret=(float)temp;
			return ret;
		}

		return 0;
		
	}	
//////////////////////////////////////////////////////////////////// 	
	public void AllMsg(OscMessage oscMessage) 
	{	
		Debug.Log("State: "+Osc.OscMessageToString(oscMessage));
		
	}	
////////////////////////////////////////////////////////////////////		
	public void arduinoHandler(OscMessage oscMessage) 
	{
		int arduinoState = (int) oscMessage.Values[0];
		if (arduinoState==4) {
			led1Connected = true;
			led2Connected = true;
		}
		else if (arduinoState==5) {
			led1Connected = true;
			led2Connected = false;				
		}
		else if (arduinoState==6) {
			led1Connected = false;
			led2Connected = true;
		}
		else if (arduinoState==7) {
			led1Connected = false;
			led2Connected = false;				
		}			
		else Debug.Log("Unknown Arduino State: "+arduinoState.ToString());
	}
//////////////////////////////////////////////////////////////////// 
	void Update () {
		
		// Check if the state of the leds has changed
		if (wasLed1On != led1On || wasLed2On != led2On) {
			hasLedStatusChanged = true;
			currentChangeSignal = 0;
		}
		
		// If the status has changed, send a specified number of OSC
		// messages to inform openFrameworks of the change
		if (hasLedStatusChanged) {
			if (currentChangeSignal<numberChangeSignals) {
				OscMessage m = new OscMessage();
				m.Address = "/unity/state";
				ArrayList state = new ArrayList();
				if (led1On && led2On) state.Add(0);
				else if (led1On && !led2On) state.Add(1);
				else if (!led1On && led2On) state.Add(2);
				else if (!led1On && !led2On) state.Add(3);
				m.Values = state;
				handler.Send(m);
				}
			currentChangeSignal++;
		}
		 
		wasLed1On = led1On;
		wasLed2On = led2On;
	
	}
//////////////////////////////////////////////////////////////////// 
}
