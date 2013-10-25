using UnityEngine;
using System.Collections;

public class ParticleEmitterFollow : MonoBehaviour {
	public Transform player;
	public float height;
	
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 newPosition = Vector3.zero;
		newPosition.x = player.position.x;
		newPosition.y = height;
		newPosition.z = player.position.z;
		transform.position = newPosition;
	
	}
}
