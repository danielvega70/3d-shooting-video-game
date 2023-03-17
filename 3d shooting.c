using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public GameObject gun;
    public float shootDelay = 0.5f;
    private bool canShoot = true;
    private Animator animator;

    void Start()
    {
        animator = GetComponent<Animator>();
    }

    void Update()
    {
        if (Input.GetButtonDown("Fire1") && canShoot)
        {
            animator.SetTrigger("Shoot"); // trigger the shoot animation
            Shoot(); // execute the shoot function
            canShoot = false; // prevent the player from shooting again immediately
            StartCoroutine(ResetShootDelay()); // start a coroutine to reset the shooting delay
        }
    }

    void Shoot()
    {
        // create a bullet object and add force to it
        GameObject bullet = Instantiate(gun, transform.position, Quaternion.identity);
        Rigidbody bulletRb = bullet.GetComponent<Rigidbody>();
        bulletRb.AddForce(transform.forward * 1000);
    }

    IEnumerator ResetShootDelay()
    {
        yield return new WaitForSeconds(shootDelay);
        canShoot = true;
    }
}
