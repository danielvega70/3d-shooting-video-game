using UnityEngine;
using UnityEngine.AI;

public class NPC : MonoBehaviour
{
    public Transform target;
    public float lookRadius = 10f;

    private NavMeshAgent agent;
    private Animator animator;

    private void Start()
    {
        agent = GetComponent<NavMeshAgent>();
        animator = GetComponent<Animator>();
    }

    private void Update()
    {
        float distance = Vector3.Distance(target.position, transform.position);

        if (distance <= lookRadius)
        {
            agent.SetDestination(target.position);

            if (distance <= agent.stoppingDistance)
            {
                FaceTarget();
                animator.SetBool("isWalking", false);
                animator.SetBool("isAttacking", true);
            }
            else
            {
                animator.SetBool("isWalking", true);
                animator.SetBool("isAttacking", false);
            }
        }
        else
        {
            animator.SetBool("isWalking", false);
            animator.SetBool("isAttacking", false);
        }
    }

    void FaceTarget()
    {
        Vector3 direction = (target.position - transform.position).normalized;
        Quaternion lookRotation = Quaternion.LookRotation(new Vector3(direction.x, 0, direction.z));
        transform.rotation = Quaternion.Slerp(transform.rotation, lookRotation, Time.deltaTime * 5f);
    }

    private void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(transform.position, lookRadius);
    }
}
