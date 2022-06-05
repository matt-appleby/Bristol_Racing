-- Variable oscillator code

-- The code should implement a variable square wave oscillator that can
-- be fed by an arduino single bus that can output to a gate driver

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--variable BusBits : integer := 3;-- base 0 Using 3 for now as my prewritten examples are all 4 bit, move to 8 bit later
--Higher bits give more frquency options but slower switching rates
-- could have some funky supercharge feature so change number of bits to allow for faster switching but would be v diff

entity VarSqrOsc is
    --constant BusBits : integer := 3;-- base 0 Using 3 for now as my prewritten examples are all 4 bit, move to 8 bit later
    port(
        --input    
        ArdClk : in std_logic;
        ArdOut : in std_logic;
        ArdSel : in std_logic;
        Clk: in std_logic;

        --output
        ToDrive : out std_logic
        --Testing outputs 
        --SIPO1 : out std_logic_vector(3 downto 0);
        --SIPO2 : out std_logic_vector(3 downto 0);
        --Count : out std_logic_vector(3 downto 0);
    );
end;

architecture synth of VarSqrOsc is

    component UP_COUNTER is
        port(
            clk, reset : in std_logic;
            counter : out std_logic_vector(3 downto 0)
        );
    end component;

    component sipo is
        port(
            clk, clear : in std_logic;
            Input_Data: in std_logic;
            Q: out std_logic_vector(3 downto 0)
        );
    end component;

    component toggle_select is
        --two buses are inputed and a toggle is used to select
        -- which is outputted
        --Implementation still needs writing
        port(
            A : in std_logic_vector(3 downto 0);
            B : in std_logic_vector(3 downto 0);
            Y : out std_logic_vector(3 downto 0);
            Sel : in std_logic
        );
        end component;

    component GreaterThanComparison is
        --compares signal a to b and outputs binary
        port(
            A : in std_logic_vector(3 downto 0);
            B : in std_logic_vector(3 downto 0);
            Y : out std_logic
        );
        end component;

    component dff is
        port(
            Q : out std_logic;
            Clk : in std_logic;
            clr : in std_logic;
            D : in std_logic
        );
    end component;


--resetSipo1
--resetSipo2
--ArdOut needs some block to interface
begin
counter : UP_COUNTER port map(clk => clk, reset => clrclk, counter => TSys);
TimeReg1 : sipo port map(clk => ArdClk, clear  => resetSipo1, Input_Data => ArdOut, Q => T1);--ArdOut needs work
TimeReg2 : sipo port map(clk => ArdClk, clear  => resetSipo2, Input_Data => ArdOut, Q => T2);
TogSel : Toggle_Select port map(A => T1, B => T2, Y=> TSel); -- Need to build this
GreatThan : Greater_Than port map(A => TSel, B => TSys, Y => OutClk); -- Need to build this
out_flop : dff port map(clk => blip, clr => clrclk, D => not dp, Q=>dp);--Not sure about this
end synth;