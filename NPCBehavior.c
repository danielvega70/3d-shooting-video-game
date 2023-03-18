using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPCBehavior : MonoBehaviour
{
    // Define the input layer size and the hidden layer size
    private int inputLayerSize = 2;
    private int hiddenLayerSize = 3;

    // Define the weights for the neural network
    private float[,] weightsIH = new float[,] { {-0.5f, 0.5f, 0.5f}, {0.5f, -0.5f, -0.5f} };
    private float[,] weightsHO = new float[,] { {0.5f, -0.5f, 0.5f} };

    // Define the bias values for the neural network
    private float[] biasH = new float[] { 0.5f, -0.5f, 0.5f };
    private float[] biasO = new float[] { -0.5f };

    // Define the input and output values for the neural network
    private float[] input = new float[2];
    private float[] hiddenOutputs = new float[3];
    private float[] outputs = new float[1];

    // Define the speed and direction of the NPC movement
    private float speed = 0.1f;
    private Vector3 direction = Vector3.right;

    void Start()
    {
        // Initialize the input values
        input[0] = Random.Range(-1f, 1f);
        input[1] = Random.Range(-1f, 1f);
    }

    void Update()
    {
        // Feed forward the input values through the neural network
        for (int i = 0; i < hiddenLayerSize; i++)
        {
            float sum = 0f;
            for (int j = 0; j < inputLayerSize; j++)
            {
                sum += input[j] * weightsIH[j, i];
            }
            sum += biasH[i];
            hiddenOutputs[i] = (float)Mathf.Tanh(sum);
        }

        for (int i = 0; i < outputs.Length; i++)
        {
            float sum = 0f;
            for (int j = 0; j < hiddenLayerSize; j++)
            {
                sum += hiddenOutputs[j] * weightsHO[j, i];
            }
            sum += biasO[i];
            outputs[i] = (float)Mathf.Tanh(sum);
        }

        // Adjust the direction of the NPC movement based on the output values
        if (outputs[0] < -0.5f)
        {
            direction = Vector3.right;
        }
        else if (outputs[0] > 0.5f)
        {
            direction = Vector3.left;
        }
        else
        {
            direction = Vector3.zero;
        }

        // Move the NPC
        transform.Translate(direction * speed * Time.deltaTime);
    }
}
