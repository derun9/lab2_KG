#version 460 core
out vec4 FragColor;
uniform float timeValue;

void main()
{
    // ���������� timeValue ��� ���������� ������
    float r = sin(timeValue) * 0.5f + 0.5f; // Red color
    float g = sin(timeValue + 2.0f) * 0.5f + 0.5f; // Green color
    float b = sin(timeValue + 4.0f) * 0.5f + 0.5f; // Blue color

    // ������� ��������� ����
    FragColor = vec4(r, g, b, 1.0f);
}
