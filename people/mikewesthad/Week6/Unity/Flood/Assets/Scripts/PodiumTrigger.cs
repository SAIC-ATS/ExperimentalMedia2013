using UnityEngine;
using System.Collections;

public class PodiumTrigger : MonoBehaviour {
	
	public Transform instructionsText;
	
	// Use this for initialization
	void Start () {
		instructionsText.gameObject.SetActive(false);
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void OnTriggerEnter(Collider other) {
		instructionsText.gameObject.SetActive(true);	
	}
	
	void OnTriggerExit(Collider other) {
		instructionsText.gameObject.SetActive(false);	
	}
	
	void OnTriggerStay(Collider other) {
		float rotation = 45.0f * Time.deltaTime;
		Vector3 axis = new Vector3(0, 1, 0);
		Vector3 point = transform.parent.position;
		instructionsText.RotateAround(point, axis, rotation);
	}
}
