using System;
using System.Runtime.InteropServices;
using UnityEngine;

public struct Entity
{
    public readonly int raw;
}

public unsafe class Bootstrap : MonoBehaviour
{
    private void* simulation;

    public static void LogError(IntPtr message)
    {
        Debug.LogError(Marshal.PtrToStringUTF8(message));
    }
    
    public static void LogMessage(IntPtr message)
    {
        Debug.Log(Marshal.PtrToStringUTF8(message));
    }

    // Start is called before the first frame update
    void Start()
    {
        AsteroidsSimulation.Initialize();
        AsteroidsSimulation.setupCallbacks(
            (void*)Marshal.GetFunctionPointerForDelegate(new Action<IntPtr>(LogError)),
            (void*)Marshal.GetFunctionPointerForDelegate(new Action<IntPtr>(LogMessage))
            );

        var settings = new AsteroidsSimulation.SimulationSettings()
        {
            mapSize = new Vector2(16, 9),
            asteroidSizeRange = new Vector2(0.25f, 1f),
            asteroidSpeedRange = new Vector2(0.1f, 0.3f),
            initialAsteroidCount = 10f,
            shipRotationSpeed = 1f,
            shipAcceleration = 1f,
        };
        
        simulation = AsteroidsSimulation.instantiate(settings);
    }

    private void OnDestroy()
    {
        AsteroidsSimulation.dispose(simulation);
        AsteroidsSimulation.Dispose();
    }

    private void FixedUpdate()
    {
        var steer = new Vector2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"));
        AsteroidsSimulation.sendCommand(simulation, new AsteroidsSimulation.UserInputCommand() { steer = steer });
        AsteroidsSimulation.update(simulation);
    }

    private void OnDrawGizmos()
    {
        if(simulation == null) return;
        
        var entities = AsteroidsSimulation.getBodyEntities(simulation).AsReadOnly<Entity>();
        foreach (var entity in entities)
        {
            var body = AsteroidsSimulation.getBody(simulation, entity);
            var viewRotation = Quaternion.Euler(0, 0, body.rotation * Mathf.Rad2Deg);
            Gizmos.DrawLine(body.position, body.position + (Vector2)(viewRotation * Vector2.right));
            Gizmos.DrawWireSphere(body.position, body.radius);
        }
    }
}
