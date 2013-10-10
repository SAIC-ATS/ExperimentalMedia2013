using UnityEngine;
using System.Collections;

public class PodiumLogic : MonoBehaviour {
	
	public bool isLedConnected = true;
	public bool isLedOn = true;
	
	public Transform lightSwitchOnModel;
	public Transform lightSwitchOffModel;
	public Transform led;
	public Transform glowLight;
	public Transform glowParticles;
	public Transform electricRain;
	public Transform glowSounds;
	public Transform[] energyTracks;
	public Transform[] particleLights;
	
	public float glowLightOffIntensity = 1;
	public float glowLightOnIntensity = 8;
	public float energyTrackOffEmissionRate = 30;
	public float energyTrackOnEmissionRate = 300;
	public float electricRainOffEmissionRate = 300;
	public float electricRainOnEmissionRate = 1000;
	
	public AudioClip lightSwitchOn;
	public AudioClip lightSwitchOff;
	public AudioClip ledDisconnect;
	public AudioClip ledConnect;
	
	private ParticleSystem electricRainParticleSystem; 
	
	// Use this for initialization
	void Start () {
		electricRainParticleSystem = (ParticleSystem) electricRain.GetComponent("ParticleSystem");
	}
	
	public void switchLed() {
		if (isLedOn) turnLedOff();
		else turnLedOn();
	}
	
	public void switchLedConnectionState() {
		if (isLedConnected) disconnectLed();
		else connectLed();
	}
	
	public void disconnectLed() {
		if (isLedConnected) {
			isLedConnected = false;
			foreach(Transform energyTrack in energyTracks) {
				energyTrack.gameObject.SetActive(false);
				ParticleSystem ps = (ParticleSystem) energyTrack.GetComponent("ParticleSystem");
				ps.emissionRate = energyTrackOffEmissionRate;
			}
			foreach(Transform particleLight in particleLights) {
				particleLight.gameObject.SetActive(false);
			}		
			electricRainParticleSystem.emissionRate = electricRainOffEmissionRate;
			electricRain.gameObject.SetActive(false);
			glowLight.gameObject.SetActive(false);
			glowSounds.gameObject.SetActive(false);
			led.gameObject.SetActive(false);
			glowParticles.gameObject.SetActive(false);		
			isLedOn = false;
			lightSwitchOnModel.gameObject.SetActive(false);
			lightSwitchOffModel.gameObject.SetActive(true);
			lightSwitchOffModel.audio.PlayOneShot(ledDisconnect);	
		}
		
	}
	
	public void connectLed() {
		if (!isLedConnected) {
			isLedConnected = true;
			foreach(Transform energyTrack in energyTracks) {
				energyTrack.gameObject.SetActive(true);
				ParticleSystem ps = (ParticleSystem) energyTrack.GetComponent("ParticleSystem");
				ps.emissionRate = energyTrackOffEmissionRate;
			}
			foreach(Transform particleLight in particleLights) {
				particleLight.gameObject.SetActive(true);
			}
			electricRain.gameObject.SetActive(true);
			glowLight.gameObject.SetActive(true);
			glowLight.light.intensity = glowLightOffIntensity;
			(glowLight.GetComponent("Halo") as Behaviour).enabled = false;
			glowSounds.gameObject.SetActive(true);
			glowSounds.audio.volume = 0.5f;
			led.gameObject.SetActive(true);
			lightSwitchOffModel.audio.PlayOneShot(ledConnect);	
		}
	}
	
	void turnLedOff() {
		electricRainParticleSystem.emissionRate = electricRainOffEmissionRate;
		foreach(Transform energyTrack in energyTracks) {
			ParticleSystem ps = (ParticleSystem) energyTrack.GetComponent("ParticleSystem");
			ps.emissionRate = energyTrackOffEmissionRate;
		}
		isLedOn = false;
		glowParticles.gameObject.SetActive(false);
		glowLight.light.intensity = glowLightOffIntensity;
		(glowLight.GetComponent("Halo") as Behaviour).enabled = false;
		led.gameObject.SetActive(true);
		glowSounds.audio.volume = 0.5f;
		lightSwitchOnModel.gameObject.SetActive(false);
		lightSwitchOffModel.gameObject.SetActive(true);
		lightSwitchOffModel.audio.PlayOneShot(lightSwitchOff);	
		
	}
	
	void turnLedOn() {
		if (isLedConnected) {
			isLedOn = true;
			electricRainParticleSystem.emissionRate = electricRainOnEmissionRate;
			foreach(Transform energyTrack in energyTracks) {
				ParticleSystem ps = (ParticleSystem) energyTrack.GetComponent("ParticleSystem");
				ps.emissionRate = energyTrackOnEmissionRate;
			}
			glowParticles.gameObject.SetActive(true);
			glowLight.light.intensity = glowLightOnIntensity;
			(glowLight.GetComponent("Halo") as Behaviour).enabled = true;
			led.gameObject.SetActive(false);
			glowSounds.audio.volume = 1.0f;
			lightSwitchOnModel.gameObject.SetActive(true);
			lightSwitchOffModel.gameObject.SetActive(false);
			lightSwitchOnModel.audio.PlayOneShot(lightSwitchOn);	
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
