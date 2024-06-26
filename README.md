<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>PDC_A2: Speeding Up via OpenMP, TPU, and GPU</title>
</head>
<body>

<h1>🚀 Project Extension: PDC_A1</h1>

<p>This repository is an extension of the <strong>PDC_A1</strong> project. We have further enhanced the project by analyzing the speedup achieved using <strong>OpenMP</strong>, <strong>TPU</strong>, and <strong>GPU</strong>.</p>

<p>For more details, check out our comprehensive <a href="./your-document-link">document</a>.</p>

<h2>How to Run</h2>

<h3>🔄 OpenMP</h3>

<p>To compile and run the OpenMP code, use the following commands:</p>

<pre><code>gcc -fopenmp -o matrix_multiplication part1_openmp.c
./matrix_multiplication
</code></pre>

<h3>🖥️ GPU (CUDA)</h3>

<p>To run your CUDA code on Google Colab, follow these steps:</p>

<h4>Step 1: Enable GPU in Colab</h4>

<ol>
    <li>Open your Google Colab notebook.</li>
    <li>Go to the menu and click on <strong>Runtime &gt; Change runtime type</strong>.</li>
    <li>In the popup, select <strong>GPU</strong> from the dropdown menu under <strong>Hardware accelerator</strong>.</li>
    <li>Click <strong>Save</strong>.</li>
</ol>

<h4>Step 2: Write the CUDA Code to a File</h4>

<p>In your Colab notebook, create a cell to write your CUDA code to a file:</p>

<pre><code># Create a file with your CUDA code
cuda_code = """
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
"""
with open('my_code.cu', 'w') as f:
    f.write(cuda_code)
</code></pre>

<h4>Step 3: Compile the CUDA Code</h4>

<p>Create a new cell in your Colab notebook and compile the CUDA code using <code>nvcc</code>:</p>

<pre><code>!nvcc -o my_code my_code.cu
</code></pre>

<h4>Step 4: Execute the Compiled Program</h4>

<p>Create a new cell to run the compiled CUDA program:</p>

<pre><code>!./my_code
</code></pre>

<h4>Step 5: Upload and Provide Input File</h4>

<p>Upload your <code>simba.txt</code> input file to the Colab environment. You can do this by clicking on the folder icon on the left sidebar and then clicking on the upload button.</p>

<h3>🌐 TPU (TensorFlow)</h3>

<p>To run your TensorFlow code on Kaggle, follow these steps:</p>

<h4>Step 1: Create a New Kaggle Notebook</h4>

<ol>
    <li>Go to <a href="https://www.kaggle.com/">Kaggle</a>.</li>
    <li>Click on your profile icon and select <strong>Your Work</strong>.</li>
    <li>Click on <strong>New Notebook</strong>.</li>
</ol>

<h4>Step 2: Enable TPU</h4>

<ol>
    <li>In your Kaggle notebook, click on the <strong>Settings</strong> tab.</li>
    <li>Enable <strong>TPU</strong> under <strong>Accelerator</strong>.</li>
</ol>

<h4>Step 3: Upload Your Input File</h4>

<ol>
    <li>In your Kaggle notebook, click on the <strong>Add data</strong> button in the sidebar.</li>
    <li>Click on <strong>Upload</strong> and upload your <code>inputFile.txt</code>.</li>
</ol>

<h4>Step 4: Modify and Run Your Code</h4>

<p>Ensure your code reads the file from the Kaggle environment and utilizes TPU resources efficiently.</p>

<p>Happy coding! 💻✨</p>

</body>
</html>
