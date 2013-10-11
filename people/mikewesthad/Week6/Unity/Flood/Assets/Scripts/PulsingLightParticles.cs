using UnityEngine;
using System.Collections;

public class PulsingLightParticles : MonoBehaviour {
	
	private ParticleSystem lightEmitter;
	
	public float flareSize = 0.5f;
	private float timer = 0.0f;
	
	public float noiseTimeScale = 1.0f;
	public float noiseAmplitude = 0.5f;
	
	
	// Use this for initialization
	void Start () {
		lightEmitter = (ParticleSystem) transform.GetComponent("ParticleSystem");	
	}
	
	// Update is called once per frame
	void Update () {	
		float noise = noiseAmplitude * Mathf.PerlinNoise(Time.time * noiseTimeScale, 0.0f);
		lightEmitter.startSize = flareSize + noise;
	}
}
