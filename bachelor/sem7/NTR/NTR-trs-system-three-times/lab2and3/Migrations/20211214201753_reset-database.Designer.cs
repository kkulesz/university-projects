﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using lab2and3.Models.Repositories;

namespace lab2and3.Migrations
{
    [DbContext(typeof(TrsContext))]
    [Migration("20211214201753_reset-database")]
    partial class resetdatabase
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("Relational:MaxIdentifierLength", 64)
                .HasAnnotation("ProductVersion", "5.0.0");

            modelBuilder.Entity("lab2and3.Models.DomainModel.Activity", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("int");

                    b.Property<int?>("AcceptedBudget")
                        .HasColumnType("int");

                    b.Property<int?>("ActivityId")
                        .HasColumnType("int");

                    b.Property<int>("Budget")
                        .HasColumnType("int");

                    b.Property<string>("Code")
                        .HasColumnType("text");

                    b.Property<DateTime>("CreatedAt")
                        .HasColumnType("datetime");

                    b.Property<DateTime>("Date")
                        .HasColumnType("datetime");

                    b.Property<string>("Description")
                        .HasColumnType("text");

                    b.Property<string>("Executor")
                        .HasColumnType("text");

                    b.Property<bool>("IsActive")
                        .HasColumnType("tinyint(1)");

                    b.Property<string>("Project")
                        .HasColumnType("text");

                    b.Property<DateTime>("RowVersion")
                        .IsConcurrencyToken()
                        .ValueGeneratedOnAddOrUpdate()
                        .HasColumnType("datetime");

                    b.HasKey("Id");

                    b.HasIndex("ActivityId");

                    b.ToTable("Activities");
                });

            modelBuilder.Entity("lab2and3.Models.DomainModel.Project", b =>
                {
                    b.Property<byte[]>("ProjectId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("varbinary(16)");

                    b.Property<int>("Budget")
                        .HasColumnType("int");

                    b.Property<DateTime>("CreatedAt")
                        .HasColumnType("datetime");

                    b.Property<bool>("IsActive")
                        .HasColumnType("tinyint(1)");

                    b.Property<string>("Name")
                        .HasColumnType("text");

                    b.Property<string>("Owner")
                        .HasColumnType("text");

                    b.HasKey("ProjectId");

                    b.ToTable("Projects");
                });

            modelBuilder.Entity("lab2and3.Models.DomainModel.User", b =>
                {
                    b.Property<byte[]>("UserId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("varbinary(16)");

                    b.Property<DateTime>("CreatedAt")
                        .HasColumnType("datetime");

                    b.Property<string>("Login")
                        .HasMaxLength(50)
                        .HasColumnType("varchar(50)");

                    b.Property<byte[]>("ProjectId")
                        .HasColumnType("varbinary(16)");

                    b.HasKey("UserId");

                    b.HasIndex("ProjectId");

                    b.ToTable("Users");
                });

            modelBuilder.Entity("lab2and3.Models.DomainModel.UsersMonth", b =>
                {
                    b.Property<byte[]>("UsersMonthId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("varbinary(16)");

                    b.Property<DateTime>("CreatedAt")
                        .HasColumnType("datetime");

                    b.Property<bool>("Frozen")
                        .HasColumnType("tinyint(1)");

                    b.Property<int>("Month")
                        .HasColumnType("int");

                    b.Property<string>("UserLogin")
                        .HasMaxLength(50)
                        .HasColumnType("varchar(50)");

                    b.Property<int>("Year")
                        .HasColumnType("int");

                    b.HasKey("UsersMonthId");

                    b.ToTable("UsersMonths");
                });

            modelBuilder.Entity("lab2and3.Models.DomainModel.Activity", b =>
                {
                    b.HasOne("lab2and3.Models.DomainModel.Activity", null)
                        .WithMany("Subactivities")
                        .HasForeignKey("ActivityId");
                });

            modelBuilder.Entity("lab2and3.Models.DomainModel.User", b =>
                {
                    b.HasOne("lab2and3.Models.DomainModel.Project", null)
                        .WithMany("Users")
                        .HasForeignKey("ProjectId");
                });

            modelBuilder.Entity("lab2and3.Models.DomainModel.Activity", b =>
                {
                    b.Navigation("Subactivities");
                });

            modelBuilder.Entity("lab2and3.Models.DomainModel.Project", b =>
                {
                    b.Navigation("Users");
                });
#pragma warning restore 612, 618
        }
    }
}
