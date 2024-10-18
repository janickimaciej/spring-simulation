#include "guis/controlPanel.hpp"

#include <imgui/imgui.h>

#include <algorithm>

ControlPanel::ControlPanel(Simulation& simulation, const glm::ivec2& windowSize) :
	m_simulation{simulation},
	m_windowSize{windowSize}
{ }

void ControlPanel::update()
{
	ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({200, static_cast<float>(m_windowSize.y)}, ImGuiCond_Always);
	ImGui::Begin("controlPanel", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

	if (ImGui::Button("Start"))
	{
		m_simulation.start();
	}

	ImGui::Spacing();

	if (ImGui::Button("Stop"))
	{
		m_simulation.stop();
	}

	separator();

	updateValue
	(
		[this] () { return m_simulation.getDT(); },
		[this] (float dt) { m_simulation.setDT(dt); },
		"dt",
		0.01f
	);

	updateValue
	(
		[this] () { return m_simulation.getM(); },
		[this] (float m) { m_simulation.setM(m); },
		"m",
		0.1f
	);

	updateValue
	(
		[this] () { return m_simulation.getC(); },
		[this] (float c) { m_simulation.setC(c); },
		"c",
		0.1f
	);

	updateValue
	(
		[this] () { return m_simulation.getK(); },
		[this] (float k) { m_simulation.setK(k); },
		"k",
		0.0f
	);

	updateValue
	(
		[this] () { return m_simulation.getX0(); },
		[this] (float x0) { m_simulation.setX0(x0); },
		"x0"
	);

	updateValue
	(
		[this] () { return m_simulation.getV0(); },
		[this] (float v0) { m_simulation.setV0(v0); },
		"v0"
	);

	separator();

	ImGui::Text("w(t)");

	{
		static const std::string wSuffix = "##controlPanelW";
		int wFunctionType = static_cast<int>(m_simulation.getWFunctionType());
		ImGui::RadioButton(("None" + wSuffix).c_str(), &wFunctionType,
			static_cast<int>(Simulation::FunctionType::none));
		ImGui::RadioButton(("Constant" + wSuffix).c_str(), &wFunctionType,
			static_cast<int>(Simulation::FunctionType::constant));
		ImGui::RadioButton(("Step" + wSuffix).c_str(), &wFunctionType,
			static_cast<int>(Simulation::FunctionType::step));
		ImGui::RadioButton(("Periodic step" + wSuffix).c_str(), &wFunctionType,
			static_cast<int>(Simulation::FunctionType::stepPeriodic));
		ImGui::RadioButton(("Sinus" + wSuffix).c_str(), &wFunctionType,
			static_cast<int>(Simulation::FunctionType::sinus));
		m_simulation.setWFunctionType(static_cast<Simulation::FunctionType>(wFunctionType));
	}
	
	Simulation::FunctionType wFunctionType = m_simulation.getWFunctionType();

	if (wFunctionType != Simulation::FunctionType::none)
	{
		updateValue
		(
			[this] () { return m_simulation.getWA(); },
			[this] (float a) { m_simulation.setWA(a); },
			"A##w",
			0.0f
		);
	}

	if (wFunctionType == Simulation::FunctionType::stepPeriodic ||
		wFunctionType == Simulation::FunctionType::sinus)
	{
		updateValue
		(
			[this] () { return m_simulation.getWOmega(); },
			[this] (float omega) { m_simulation.setWOmega(omega); },
			"omega##w",
			0.1f
		);

		updateValue
		(
			[this] () { return m_simulation.getWPhi(); },
			[this] (float phi) { m_simulation.setWPhi(phi); },
			"phi##w"
		);
	}
	
	if (wFunctionType == Simulation::FunctionType::step)
	{
		updateValue
		(
			[this] () { return m_simulation.getWT0(); },
			[this] (float t0) { m_simulation.setWT0(t0); },
			"t0##w"
		);
	}
	
	separator();

	ImGui::Text("h(t)");

	{
		static const std::string hSuffix = "##controlPanelH";
		int hFunctionType = static_cast<int>(m_simulation.getHFunctionType());
		ImGui::RadioButton(("None" + hSuffix).c_str(), &hFunctionType,
			static_cast<int>(Simulation::FunctionType::none));
		ImGui::RadioButton(("Constant" + hSuffix).c_str(), &hFunctionType,
			static_cast<int>(Simulation::FunctionType::constant));
		ImGui::RadioButton(("Step" + hSuffix).c_str(), &hFunctionType,
			static_cast<int>(Simulation::FunctionType::step));
		ImGui::RadioButton(("Periodic step" + hSuffix).c_str(), &hFunctionType,
			static_cast<int>(Simulation::FunctionType::stepPeriodic));
		ImGui::RadioButton(("Sinus" + hSuffix).c_str(), &hFunctionType,
			static_cast<int>(Simulation::FunctionType::sinus));
		m_simulation.setHFunctionType(static_cast<Simulation::FunctionType>(hFunctionType));
	}

	Simulation::FunctionType hFunctionType = m_simulation.getHFunctionType();

	if (hFunctionType != Simulation::FunctionType::none)
	{
		updateValue
		(
			[this] () { return m_simulation.getHA(); },
			[this] (float a) { m_simulation.setHA(a); },
			"A##h",
			0.0f
		);
	}

	if (hFunctionType == Simulation::FunctionType::stepPeriodic ||
		hFunctionType == Simulation::FunctionType::sinus)
	{
		updateValue
		(
			[this] () { return m_simulation.getHOmega(); },
			[this] (float omega) { m_simulation.setHOmega(omega); },
			"omega##h",
			0.1f
		);

		updateValue
		(
			[this] () { return m_simulation.getHPhi(); },
			[this] (float phi) { m_simulation.setHPhi(phi); },
			"phi##h"
		);
	}
	
	if (hFunctionType == Simulation::FunctionType::step)
	{
		updateValue
		(
			[this] () { return m_simulation.getHT0(); },
			[this] (float t0) { m_simulation.setHT0(t0); },
			"t0##h"
		);
	}
	
	ImGui::End();
}

void ControlPanel::updateValue(const std::function<float()>& get,
	const std::function<void(float)>& set, const std::string& name, std::optional<float> min)
{
	static const std::string suffix = "##controlPanel";
	static constexpr float stepPrecision = 0.1f;
	static const std::string format = "%.2f";

	float value = get();
	float prevValue = value;
	ImGui::InputFloat((name + suffix).c_str(), &value, stepPrecision, stepPrecision,
		format.c_str());
	if (min.has_value())
	{
		value = std::max(value, *min);
	}
	if (value != prevValue)
	{
		set(value);
	}
}

void ControlPanel::separator()
{
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
}
