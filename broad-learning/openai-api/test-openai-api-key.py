from openai import OpenAI
import os

print(os.getenv('OPENAI_API_KEY'))
# Set your API key
#OpenAI.api_key = "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"

client = OpenAI()

completion = client.chat.completions.create(
    model="gpt-3.5-turbo",
    messages=[
        {"role": "system", "content": "You are a poetic assistant, skilled in explaining complex programming concepts with creative flair."},
        {"role": "user", "content": "Compose a poem that explains the concept of recursion in programming."}
    ],
    timeout=60  # Set the timeout value in seconds
)

print(completion.choices[0].message)