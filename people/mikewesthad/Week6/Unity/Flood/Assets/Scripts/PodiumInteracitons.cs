using UnityEngine;
using System.Collections;

public class PodiumInteracitons : MonoBehaviour {
	
	private Transform interactablePodium;
	
	public Transform podium1;
	public Transform podium2;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if ((Input.GetKeyDown(KeyCode.LeftShift)||Input.GetMouseButtonDown(0)) && interactablePodium!=null) {
			print ("Mouse 0");
			
			
			Ray ray = Camera.main.ScreenPointToRay(new Vector3(Screen.width/2, Screen.height/2, 0));
		    RaycastHit hitInfo;
		    if (Physics.Raycast(ray, out hitInfo, 20)) {
				if (hitInfo.collider.gameObject.tag == "Podium") {
					PodiumLogic script = (PodiumLogic)interactablePodium.GetComponent("PodiumLogic");
					script.switchLed();
				}
				if (hitInfo.collider.gameObject.tag == "Nature") {
					
					PodiumLogic script1 = (PodiumLogic)podium1.GetComponent("PodiumLogic");
					PodiumLogic script2 = (PodiumLogic)podium2.GetComponent("PodiumLogic");
					
					if (!script1.isLedConnected && !script2.isLedConnected) {
						NatureLogic script = (NatureLogic)interactablePodium.GetComponent("NatureLogic");
						script.turnOn();
					}
				}
		    }
			
			
		}
		if ((Input.GetKeyDown(KeyCode.LeftControl)||Input.GetMouseButtonDown(1)) && interactablePodium!=null) {
			print ("Mouse 1");
			
			Ray ray = Camera.main.ScreenPointToRay(new Vector3(Screen.width/2, Screen.height/2, 0));
		    RaycastHit hitInfo;
		    if (Physics.Raycast(ray, out hitInfo, 20)) {
				if (hitInfo.collider.gameObject.tag == "Podium") {
					PodiumLogic script = (PodiumLogic)interactablePodium.GetComponent("PodiumLogic");
					script.switchLedConnectionState();
				}
		    }
			
		}
	}
	
	void OnTriggerEnter(Collider other) {
		interactablePodium = other.transform.parent;	
	}
	
	void OnTriggerExit(Collider other) {
		interactablePodium = null;	
	}
	
}
