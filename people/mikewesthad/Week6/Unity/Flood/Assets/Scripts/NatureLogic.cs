using UnityEngine;
using System.Collections;

public class NatureLogic : MonoBehaviour {

	public Transform player;
	
	public bool isPowered = false;
	public bool isOn = true;
	
	public Transform lightSwitchOnModel;
	public Transform lightSwitchOffModel;
	public Transform glowLight;
	public Transform glowParticles;
	public Transform electricRain;
	public Transform glowSounds;
	
	public AudioClip lightSwitchOn;
	public AudioClip lightSwitchOff;
	
	private ParticleSystem electricRainParticleSystem;
	
	private float timeSinceOn = 0.0f;
	
	// Use this for initialization
	void Start () {
		electricRainParticleSystem = (ParticleSystem) electricRain.GetComponent("ParticleSystem");
	}
	
	public void turnOn() {
		isOn = true;
		electricRainParticleSystem.gameObject.SetActive(true);
		glowParticles.gameObject.SetActive(true);
		lightSwitchOnModel.gameObject.SetActive(true);
		lightSwitchOffModel.gameObject.SetActive(false);	
		glowLight.gameObject.SetActive(true);
		glowSounds.gameObject.SetActive(true);
	}
	
	// Update is called once per frame
	void Update () {
		
		if (isOn) {
			timeSinceOn += Time.deltaTime;
			ParticleSystem ps = (ParticleSystem) glowParticles.GetComponent("ParticleSystem");
			if (timeSinceOn > 1 && timeSinceOn < 20) ps.startSize = Mathf.Pow(1.1f, timeSinceOn-1)-1;
			else ps.startSize = Mathf.Pow(1.1f, 20-1)-1;
			 
//				0.1f * Time.deltaTime;
//			Vector3 newPos = player.position;
//			newPos.y = 7;
//			electricRain.position = newPos;
		}
	
	}
}
