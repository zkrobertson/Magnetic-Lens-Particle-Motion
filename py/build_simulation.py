# Method types with additional information that can be provided
method_types = {
    "single": ["x", "y", "z", "mass"],
    "monte": ["iterations", "available_masses", "random_position_function"],
}


class SimulationSetting:
    def __init__(
        self,
        vector_field,
        method,
        pass_energy,
        log_filename,
    ) -> None:
        self.info_dic = {
            "vector_field": vector_field,
            "method": method,
            "pass_energy": pass_energy,
            "log_filename": log_filename,
        }

        self.output = ""
        for key in self.info_dic:
            self.output += f"{self.info_dic[key]}\n"

    def add_single_info(self, x, y, z, mass):
        self.output += f"{x}\n{y}\n{z}\n{mass}\n"

    def add_monte_info(
        self, iterations: int, available_masses: list, random_position_function: str
    ):
        self.output += f"{iterations}\n"
        for mass in available_masses:
            self.output += f"{mass},"
        self.output += f"\n{random_position_function}"

    def write_setting_file(self, path: str) -> str:
        with open(path, "w") as file:
            file.write(self.output)

        return self.output


def main():
    mySim = SimulationSetting(
        vector_field="path",
        method="single",
        pass_energy=300,
        log_filename="path",
    )

    output = mySim.write_setting_file("./test.txt")
    print(output)


if __name__ == "__main__":
    main()
