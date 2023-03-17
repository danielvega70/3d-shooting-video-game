using UnityEngine;
using UnityEngine.Networking;

public class ShootingGame : NetworkBehaviour
{
    public GameObject bulletPrefab;
    public Transform bulletSpawn;
    public float bulletSpeed = 10.0f;

    private void Update()
    {
        // Only the local player can shoot
        if (!isLocalPlayer)
        {
            return;
        }

        // Handle shooting logic
        if (Input.GetKeyDown(KeyCode.Space))
        {
            CmdFire();
        }
    }

    [Command]
    void CmdFire()
    {
        // Create the bullet on the server
        GameObject bullet = Instantiate(bulletPrefab, bulletSpawn.position, bulletSpawn.rotation);

        // Apply velocity to the bullet
        Rigidbody rb = bullet.GetComponent<Rigidbody>();
        rb.velocity = bullet.transform.forward * bulletSpeed;

        // Spawn the bullet on the clients
        NetworkServer.Spawn(bullet);

        // Destroy the bullet after 2 seconds
        Destroy(bullet, 2.0f);
    }
}
