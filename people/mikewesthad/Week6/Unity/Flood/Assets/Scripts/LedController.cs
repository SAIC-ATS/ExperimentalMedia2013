using UnityEngine;
using System.Collections;

public class LedController : MonoBehaviour {
		
	public Transform oscObject;
	C_Receiver oscScript;
	
	public Transform podium1;
	public Transform podium2;
	
	private PodiumLogic podium1Logic;
	private PodiumLogic podium2Logic;
	
	private bool wasLed1Connected = true;
	private bool wasLed2Connected = true;
	
	
	void Start () {
		podium1Logic = (PodiumLogic) podium1.GetComponent("PodiumLogic");
		podium2Logic = (PodiumLogic) podium2.GetComponent("PodiumLogic");
		oscScript = (C_Receiver) oscObject.GetComponent("C_Receiver");
	}
		
	void Update () {	
		
		// Check the osc script to see if the LEDs have been disconnected or connected
		bool isLed1Connected = oscScript.led1Connected;
		bool isLed2Connected = oscScript.led2Connected;
		
		Debug.Log(isLed1Connected);
		if (isLed1Connected != wasLed1Connected) {
			if (isLed1Connected) {
				podium1Logic.connectLed();
			}
			else {
				podium1Logic.disconnectLed();
			}
		}
		
		if (isLed2Connected != wasLed2Connected) {
			if (isLed2Connected) {
				podium2Logic.connectLed();
			}
			else {
				podium2Logic.disconnectLed();
			}
		}
		
		wasLed1Connected = isLed1Connected;
		wasLed2Connected = isLed2Connected;
		
		// Tell the osc script whether the in-game LEDs are switched on or off
		oscScript.led1On = podium1Logic.isLedOn; 
		oscScript.led2On = podium2Logic.isLedOn; 
		
		
	}
}
