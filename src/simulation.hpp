#pragma once

#include <glm/glm.hpp>

#include <chrono>
#include <functional>
#include <vector>

class Simulation
{
	using Callback = std::function<void(float, float)>;

public:
	enum class FunctionType
	{
		none,
		constant,
		step,
		stepPeriodic,
		sinus
	};

	Simulation(const Callback& setXAndWCallback);
	void update();
	void stop();
	void start();

	float getDT() const;
	void setDT(float dt);
	float getM() const;
	void setM(float m);
	float getC() const;
	void setC(float c);
	float getK() const;
	void setK(float k);
	float getX0() const;
	void setX0(float x0);
	float getV0() const;
	void setV0(float v0);

	FunctionType getWFunctionType() const;
	void setWFunctionType(FunctionType type);
	float getWA() const;
	void setWA(float a);
	float getWOmega() const;
	void setWOmega(float omega);
	float getWPhi() const;
	void setWPhi(float phi);
	float getWT0() const;
	void setWT0(float t0);

	FunctionType getHFunctionType() const;
	void setHFunctionType(FunctionType type);
	float getHA() const;
	void setHA(float a);
	float getHOmega() const;
	void setHOmega(float omega);
	float getHPhi() const;
	void setHPhi(float phi);
	float getHT0() const;
	void setHT0(float t0);

	int getIterations() const;
	float getT() const;
	const float* getTVector() const;
	const float* getXVector() const;
	const float* getVVector() const;
	const float* getAVector() const;
	const float* getWVector() const;
	const float* getFVector() const;
	const float* getGVector() const;
	const float* getHVector() const;

private:
	Callback m_setXAndWCallback{};
	bool m_running = false;

	float m_dt = 0.01f;
	float m_m = 1;
	float m_c = 1;
	float m_k = 1;
	float m_x0 = 0;
	float m_v0 = 0;

	FunctionType m_wFunctionType = FunctionType::none;
	float m_wA = 1;
	float m_wOmega = glm::radians(90.0f);
	float m_wPhi = 0;
	float m_wT0 = 1;

	FunctionType m_hFunctionType = FunctionType::none;
	float m_hA = 1;
	float m_hOmega = glm::radians(90.0f);
	float m_hPhi = 0;
	float m_hT0 = 1;

	std::chrono::time_point<std::chrono::system_clock> m_t0{};
	std::vector<float> m_t{};
	std::vector<float> m_x{};
	std::vector<float> m_v{};
	std::vector<float> m_a{};
	std::vector<float> m_w{};
	std::vector<float> m_f{};
	std::vector<float> m_g{};
	std::vector<float> m_h{};

	float getTime() const;
	void resetTime();
	float getW(float t) const;
	float getF(float t, float x) const;
	float getG(float v) const;
	float getH(float t) const;
	glm::vec2 getRHS(const glm::vec2& state, float t) const;
};
